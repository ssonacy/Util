#pragma once

#include "SocketDefine.h"
#include "Thread.h"
#include <vector>

// 1 : 1 서버 - 클라이언트 구조
class CServerSocket
{
public:

	CServerSocket(SocketType Type);
	~CServerSocket();

	BOOL Init( int Port , DWORD* ErrorCode );
	BOOL SetSocketOpt( int SocketOpt , BOOL Enable );
	int Send( LPBYTE Data , int Size );
	void Clear();

	inline void SetAcceptCallback( AcceptCallbackType Callback )			{ m_AcceptCallback = Callback; }
	inline void SetDisconnectCallback( DisconnectCallbackType Callback )	{ m_DisconnectCallback = Callback; }
	inline void SetRecvCallback( RecvCallbackType Callback )				{ m_RecvCallback = Callback; }

private:
	
	int _send( SOCKET socket , LPBYTE EncryptData , int Size );
	BOOL _accept();
	int  _recv( char* Buffer , int BufferSize );

	static unsigned int __stdcall _recv_process_stub( void* param );
		unsigned int __stdcall _recv_process();

private:

	SOCKET _server_socket = INVALID_SOCKET;
	SOCKET _client_socket = INVALID_SOCKET;

	SOCKADDR_IN _serv_addr;
	SocketType  _type;

	CThread _recv_thread;

	AcceptCallbackType		m_AcceptCallback;	 
	DisconnectCallbackType	m_DisconnectCallback;
	RecvCallbackType		m_RecvCallback;
	

	std::vector<BYTE> _recv_buffer;
};