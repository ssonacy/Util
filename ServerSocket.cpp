#include "stdafx.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

CServerSocket::CServerSocket(SocketType Type) : _type(Type) {}
CServerSocket::~CServerSocket() { Clear(); }

BOOL CServerSocket::Init( int Port , DWORD* ErrorCode )
{
	Clear();
	
	if ( _type == SocketType::TCP ) _server_socket = socket( PF_INET , SOCK_STREAM , 0 );
	else							_server_socket = socket( PF_INET , SOCK_DGRAM  , 0 );

	if ( _server_socket == INVALID_SOCKET )
	{
		if ( ErrorCode ) *ErrorCode = WSAGetLastError();

		return FALSE;
	}

	memset(&_serv_addr, 0, sizeof(_serv_addr));

	_serv_addr.sin_family=AF_INET;
	_serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_serv_addr.sin_port=htons(Port);

	if ( SOCKET_ERROR == bind( _server_socket , (SOCKADDR*)&_serv_addr , sizeof(_serv_addr)) )
	{
		if ( ErrorCode ) *ErrorCode = WSAGetLastError();

		Clear();
		return FALSE;
	}

	if( _type == SocketType::TCP && SOCKET_ERROR == listen( _server_socket , 5 ) )
	{
		if ( ErrorCode ) *ErrorCode = WSAGetLastError();

		Clear();
		return FALSE;
	}

	_recv_thread.Start( _recv_process_stub , this , FALSE );
	return TRUE;
}

BOOL CServerSocket::SetSocketOpt( int SocketOpt , BOOL Enable )
{
	if ( _server_socket == INVALID_SOCKET ) return FALSE;

	return SOCKET_ERROR != setsockopt( _server_socket , SOL_SOCKET , SocketOpt , (char*)&Enable , sizeof(Enable));
}

int CServerSocket::_send( SOCKET socket , LPBYTE EncryptData , int Size )
{
	if ( _type == SocketType::TCP )
		return send( socket , (const char*)EncryptData , Size , 0 );

	SOCKADDR_IN ClientAddr	   = { 0 , };
	int			ClientAddrSize = sizeof(ClientAddr);

	return sendto( socket , (const char*)EncryptData , Size , 0 , (struct sockaddr*)&ClientAddr , ClientAddrSize );;
}

int CServerSocket::Send( LPBYTE Data , int Size )
{
	if ( _server_socket == INVALID_SOCKET || _client_socket == INVALID_SOCKET ) return 0;

	SOCKET Socket = (_type == SocketType::TCP) ? _client_socket : _server_socket;

	return _send( Socket , Data , Size );
}

void CServerSocket::Clear()
{
	m_AcceptCallback		= AcceptCallbackType();
	m_DisconnectCallback	= DisconnectCallbackType();
	m_RecvCallback			= RecvCallbackType();

	CLOSE_SOCKET( _server_socket );
	CLOSE_SOCKET( _client_socket );
	
	_recv_thread.Exit( INFINITE );
	_recv_buffer.clear();
}

BOOL CServerSocket::_accept()
{
	SOCKADDR_IN client_addr		 = { 0 , };
	int			client_addr_size = sizeof( SOCKADDR_IN );

	_client_socket = accept( _server_socket , (SOCKADDR*)&client_addr , &client_addr_size );

	if ( _client_socket != INVALID_SOCKET && m_AcceptCallback ) m_AcceptCallback( this );

	return ( _client_socket != INVALID_SOCKET );
}

int CServerSocket::_recv( char* Buffer , int BufferSize )
{
	if ( _type == SocketType::TCP )
		return recv( _client_socket , Buffer , BufferSize , 0 );
	
	SOCKADDR_IN ClientAddr	   = { 0 , };
	int			ClientAddrSize = sizeof(ClientAddr);

	return recvfrom( _server_socket , Buffer , BufferSize , 0 ,  (struct sockaddr*)&ClientAddr , &ClientAddrSize );
}

unsigned int __stdcall CServerSocket::_recv_process_stub( void* param )
{
	CServerSocket* pThis = (CServerSocket*)param;
	return pThis->_recv_process();
}

unsigned int CServerSocket::_recv_process()
{
	while ( !_recv_thread.IsReqStatus( ThreadReq::TERMINATING ) )
	{
		if ( _type == SocketType::TCP && !_accept() )
		{
			Sleep( 100 );
			continue;
		}

		int RecvSize = 0;
		do
		{
			char RecvBuffer[SOCKET_BUFFER] = { 0 , };
			RecvSize = _recv( RecvBuffer , SOCKET_BUFFER );

			if ( WSAEWOULDBLOCK == WSAGetLastError() ) continue;
			
			if ( RecvSize <= 0 ) break;

			_recv_buffer.insert( _recv_buffer.end() , RecvBuffer , RecvBuffer + RecvSize );
			
			PacketFlow Flow = PacketFlow::None;
			do
			{
				Flow = m_RecvCallback( this , _recv_buffer );
			} while ( Flow == PacketFlow::CallAgin );
		
		} while ( RecvSize > 0 );
		
		if ( m_DisconnectCallback ) m_DisconnectCallback( this );

		_recv_buffer.clear();
		
		CLOSE_SOCKET( _client_socket );
	}


	return 0;
}