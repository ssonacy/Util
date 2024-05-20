#include "stdafx.h"
#include "NetworkUtil.h"

#include <WinSock2.h>
#pragma comment( lib , "WS2_32.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

namespace NetUtil
{
	namespace
	{
		WSADATA _data = { 0 ,};
	};

	BOOL Init()
	{
		return WSAStartup(MAKEWORD(2,2),&_data);
	}

	void Release()
	{
		WSACleanup();
	}

	HighOrderVector<CStringA> GetIPAddress( int* ErrorCode )
	{
		char HostName[128] = { 0 , };
		gethostname( HostName , _countof(HostName) );

		struct addrinfo* info = NULL;

		int Ret = getaddrinfo( HostName , NULL , NULL , &info );
		if ( Ret != 0 )
		{
			if ( ErrorCode ) *ErrorCode = Ret;
			return HighOrderVector<CStringA>();
		}

		HighOrderVector<CStringA> AddressInfo;
		for ( addrinfo* p = info ; p != NULL ; p = p->ai_next )
		{
			char IPAddress[INET_ADDRSTRLEN] = { 0 , };

			sockaddr_in* pSocketAddress = (sockaddr_in*)p->ai_addr;
			inet_ntop( p->ai_family , &pSocketAddress->sin_addr , IPAddress , _countof(IPAddress) );

			AddressInfo.push_back( IPAddress );
		}
		
		if ( info ) freeaddrinfo( info );

		return AddressInfo;
	}
};