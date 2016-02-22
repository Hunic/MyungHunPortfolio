
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include "cSocket.h"
#include <iostream>
using namespace std;


cSocket::cSocket()
{
	m_socket = INVALID_SOCKET;
	m_socketConnect = INVALID_SOCKET;
	ZeroMemory(m_szSocketBuf, 1024);
}


cSocket::~cSocket()
{
	WSACleanup();
}

bool cSocket::InitSocket()
{
	WSADATA wsaData;
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	return true;
}
void cSocket::closeSocket(SOCKET socketClose, bool bIsForce)
{
	struct linger stLinger = { 0,0 };
	if (true == bIsForce)
		stLinger.l_onoff = 1;
	shutdown(socketClose, SD_BOTH);
	setsockopt(socketClose, SOL_SOCKET, SO_LINGER, (char*)&stLinger, sizeof(stLinger));
	closesocket(socketClose);
	socketClose = INVALID_SOCKET;
}
bool cSocket::BindandListen(int nBindPort)
{
	SOCKADDR_IN	stServerAddr;
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = htons(nBindPort);
	stServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int nRet = bind(m_socket, (SOCKADDR*)&stServerAddr, sizeof(SOCKADDR_IN));

	nRet = listen(m_socket, 5);
	cout << "���� ��� ����" << endl;

	return true;
}
bool cSocket::StartServer()
{
	char szOutStr[1024];

	SOCKADDR_IN		stClientAddr;
	int nAddrLen = sizeof(SOCKADDR_IN);

	cout << "���� ����" << endl;
	m_socketConnect = accept(m_socket, (SOCKADDR*)&stClientAddr, &nAddrLen);

	sprintf_s(szOutStr, "Ŭ���̾�Ʈ ���� : IP(%s) SOCKET(%d)", inet_ntoa(stClientAddr.sin_addr), m_socketConnect);
	cout << szOutStr << endl;

	while (1)
	{
		int nRecvLen = recv(m_socketConnect, m_szSocketBuf, 1024, 0);
		if (0 == nRecvLen)
		{
			cout << "Ŭ���̾�Ʈ�� ������ ����Ǿ����ϴ�." << endl;
			closeSocket(m_socketConnect,false);

			StartServer();
			return false;
		}
		else if (-1 == nRecvLen)
		{
			closeSocket(m_socketConnect, false);
			StartServer();
			return false;
		}
		m_szSocketBuf[nRecvLen] = NULL;
		cout << "�޼��� ���� : ���� Bytes[" << nRecvLen << "] ���� : [" << m_szSocketBuf << "]" << endl;
		int nSendLen = send(m_socketConnect, m_szSocketBuf, nRecvLen, 0);

		cout << "�޼��� �۽� : �۽� Bytes[" << nSendLen << "] ���� : [" << m_szSocketBuf << "]" << endl;
		
	}
	closeSocket(m_socketConnect, false);
	closeSocket(m_socket, false);
	cout << "���� ���� ����.." << endl;
	return true;
}
bool cSocket::Connect(char* pszIP, int nPort)
{
	SOCKADDR_IN stServerAddr;
	char szOutMsg[1024];
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = htons(nPort);
	stServerAddr.sin_addr.s_addr = inet_addr(pszIP);

	connect(m_socket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	cout << "���� ����" << endl;

	while (true)
	{
		cout << ">>";
		cin >> szOutMsg;
		if (0 == _strcmpi(szOutMsg, "quit"))
			break;
		int nSendLen = send(m_socket, szOutMsg, strlen(szOutMsg), 0);

		cout << "�޼��� �۽� : �۽� ����Ʈ [" << nSendLen << "] ����:[" << szOutMsg << "]" << endl;
		int nRecvLen = recv(m_socket, m_szSocketBuf, 1024, 0);
		m_szSocketBuf[nRecvLen] = NULL;

		cout << "�޼��� �۽� : �۽� ����Ʈ [" << nRecvLen << "] ����:[" << m_szSocketBuf << "]" << endl;
		
	}
	closeSocket(m_socket, false);
	cout << "Ŭ���̾�Ʈ ��������.." << endl;
	return true;
}
