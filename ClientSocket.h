#pragma once

#include "SocketDefine.h"

// 1 : 1 서버 - 클라이언트 구조
class CClientSocket
{
public:

	CClientSocket(SocketType Type);
	~CClientSocket();
	
	BOOL Init();
	void Clear();
	BOOL SetSocketOpt( int SocketOpt , BOOL Enable );
	BOOL Connect( const CString& IP , int Port );
	int  Send( LPBYTE Data , int Size );
	
	inline void SetRecvCallback( RecvCallbackType Callback ) { m_RecvCallback = Callback; }
	inline void SetDisconnectCallback( DisconnectCallbackType Callback ) { m_DisconnectCallback = Callback; }

private:

	int  _send( SOCKET socket , LPBYTE EncryptData , int Size );
	int  _recv( char* Buffer , int BufferSize );

	static unsigned int __stdcall _recv_process_stub( void* param );
		unsigned int _recv_process();

private:

	SOCKET  _client_socket;

	SOCKADDR_IN _server_addr;

	CThread _recv_thread;
	
	SocketType _type;

	DisconnectCallbackType	m_DisconnectCallback;
	RecvCallbackType		m_RecvCallback;

	std::vector<BYTE> _recv_buffer;
};
