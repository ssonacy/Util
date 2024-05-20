#pragma once

#include <functional>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

#define SOCKET_BUFFER (1024*64)

enum class PacketFlow
{
	None	 ,
	CallAgin ,
	MoreData ,
};

enum class SocketType { UDP , TCP };

using AcceptCallbackType		= std::function<void(void*)>;
using DisconnectCallbackType	= std::function<void(void*)>;
using RecvCallbackType			= std::function<PacketFlow(void* , std::vector<BYTE>&)>;
