
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include <winsock2.h>

class cSocket
{
public:
	cSocket();
	~cSocket();
	bool InitSocket();
	void closeSocket(SOCKET socketClose, bool bIsForce = false);
	bool BindandListen(int nBindPort);
	bool StartServer();
	bool Connect(char* pszIP, int nPort);
private:
	SOCKET m_socket;
	SOCKET m_socketConnect;
	char m_szSocketBuf[1024];
};

