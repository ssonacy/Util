#include "stdafx.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

CClientSocket::CClientSocket(SocketType Type) : _client_socket(INVALID_SOCKET) , _type(Type) {}
CClientSocket::~CClientSocket() { Clear(); }

BOOL CClientSocket::Init()
{
	Clear();

	if ( _type == SocketType::TCP ) _client_socket = socket(PF_INET, SOCK_STREAM , 0);
	else							_client_socket = socket(PF_INET, SOCK_DGRAM  , 0 );

	return (_client_socket != INVALID_SOCKET);
}

BOOL CClientSocket::SetSocketOpt( int SocketOpt , BOOL Enable )
{
	if ( _client_socket == INVALID_SOCKET ) return FALSE;

	return SOCKET_ERROR != setsockopt( _client_socket , SOL_SOCKET , SocketOpt , (char*)&Enable , sizeof(Enable));
}

void CClientSocket::Clear()
{
	m_DisconnectCallback = DisconnectCallbackType();
	m_RecvCallback		 = RecvCallbackType();

	if ( _client_socket != INVALID_SOCKET ) 
	{
		closesocket(_client_socket);
		_client_socket = INVALID_SOCKET;
	}
	
	memset( &_server_addr , 0 , sizeof( _server_addr) );

	_recv_thread.Exit( INFINITE );
	_recv_buffer.clear();
}

BOOL CClientSocket::Connect( const CString& IP , int Port )
{
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_port=htons(Port);
	inet_pton(AF_INET, (CStringA)IP, &_server_addr.sin_addr );

	if ( _type == SocketType::UDP ) return TRUE;

	if ( SOCKET_ERROR == connect( _client_socket, (SOCKADDR*)&_server_addr, sizeof(_server_addr)) )
		return FALSE;

	return _recv_thread.Start( _recv_process_stub , this , FALSE );
}

int CClientSocket::_send( SOCKET socket , LPBYTE EncryptData , int Size )
{
	if ( _type == SocketType::TCP )
		return send( socket , (const char*)EncryptData , Size , 0 );
	
	return sendto( socket , (const char*)EncryptData , Size , 0 , (struct sockaddr*)&_server_addr , sizeof(_server_addr) );
}

int CClientSocket::Send( LPBYTE Data , int Size )
{
	if ( _client_socket == INVALID_SOCKET ) return 0;

	return _send( _client_socket , Data , Size );
}

int CClientSocket::_recv( char* Buffer , int BufferSize )
{
	if ( _type == SocketType::TCP )
		return recv( _client_socket , Buffer , BufferSize , 0 );
	
	int ServerAddrSize = sizeof(_server_addr);
	return recvfrom( _client_socket , Buffer , BufferSize , 0 ,  (struct sockaddr*)&_server_addr , &ServerAddrSize );
}

unsigned int __stdcall CClientSocket::_recv_process_stub( void* param )
{
	CClientSocket* pThis = (CClientSocket*)param;
	return pThis->_recv_process();
}

unsigned int CClientSocket::_recv_process()
{
	while ( !_recv_thread.IsReqStatus( ThreadReq::TERMINATING ) )
	{
		char RecvBuffer[SOCKET_BUFFER] = { 0 , };
		int  RecvSize = _recv( RecvBuffer , SOCKET_BUFFER );

		if ( WSAEWOULDBLOCK == WSAGetLastError() ) continue;

		if ( RecvSize <= 0 || _client_socket == INVALID_SOCKET ) break;
		
		_recv_buffer.insert( _recv_buffer.end() , RecvBuffer , RecvBuffer + RecvSize );

		PacketFlow Flow = PacketFlow::None;

		do
		{
			Flow = m_RecvCallback( this , _recv_buffer );

		} while ( Flow == PacketFlow::CallAgin );
	}

	if ( m_DisconnectCallback ) m_DisconnectCallback( this );
	
	_recv_thread.Exit( 0 );
	closesocket(_client_socket);
	_client_socket = INVALID_SOCKET;

	Sleep( 100 );

	return 0;
}

