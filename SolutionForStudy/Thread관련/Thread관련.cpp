// Thread관련.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <Windows.h>
#include <process.h>
#include <thread>

volatile bool g_bIsRun = true;

unsigned int WINAPI ThreadFunc(LPVOID lpVoid)
{
	while(g_bIsRun)
	{
		cout << "Thread Func.." << endl;
	}
	cout << "Thread exit" << endl;
	return 0;
}

//int main()
//{
//	DWORD dwThreadID;
//	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, (unsigned*)&dwThreadID);
//
//	if (NULL == hThread)
//	{
//		cout << "Thread Create Fail" << endl;
//		return 0;
//	}
//	g_bIsRun = false;
//	WaitForSingleObject(hThread, INFINITE);
//	CloseHandle(hThread);
//	return 0;
//}

// TerminatedThread Example

int main()
{
	DWORD dwThreadID;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, (unsigned*)&dwThreadID);

	if (NULL == hThread)
	{
		cout << "Thread Create Fail" << endl;
		return 0;
	}
	DWORD dwExitCode = 0;
	GetExitCodeThread(hThread, &dwExitCode);
	TerminateThread(hThread, dwExitCode);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return 0;
}