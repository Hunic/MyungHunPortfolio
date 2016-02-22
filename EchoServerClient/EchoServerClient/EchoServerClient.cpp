// EchoServerClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cSocket.h"
#include <iostream>

using namespace std;


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8000

#include <Windows.h>
#include <process.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "usage : client.exe[option:[/server][/client]]" << endl;
		return 0;
	}
	cSocket Socket;
	if (_strcmpi(argv[1], "/server") == 0)
	{
		Socket.InitSocket();
		Socket.BindandListen(SERVER_PORT);
		Socket.StartServer();
	}
	else if (_strcmpi(argv[1], "/client") == 0)
	{
		Socket.InitSocket();
		Socket.Connect(SERVER_IP, SERVER_PORT);
	}
	else
	{
		cout << "usage:client.exe option:[/server][/client]" << endl;
		return 0;
	}

	return 0;
}



