#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include <MSWSock.h>
#include <ws2tcpip.h>
#include <chrono>

using namespace std::chrono_literals;

#pragma comment(lib, "ws2_32.lib")

//	38~40. 소켓 프로그래밍

//int main()
//{
//	//	윈속 초기화 (ws2_32 라이브러리 초기화)
//	//	관련 정보가 wsaData에 채워짐
//	WSAData wsaData;
//	if(::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	// ad : Address Family (AF_INET = IPv4, AF_INET6 = IPv6)
//	// type : TCP(SOCK_STREAM) vs UDP(SOCK_DGRAM)
//	// protocol : 0
//	// return : descriptor
//
//	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (clientSocket == INVALID_SOCKET)
//	{
//		int32 errCode = ::WSAGetLastError();
//		std::cout << "Socket ErrorCode : " << errCode << std::endl;
//
//		return 0;
//	}
//
//	SOCKADDR_IN serverAddr;	//	IPv4
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	//serverAddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");
//	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
//	serverAddr.sin_port = ::htons(7777);
//
//	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//	{
//		int32 errCode = ::WSAGetLastError();
//		std::cout << "Connect ErrorCode : " << errCode << std::endl;
//		return 0;
//	}
//
//	// ---------------------------------------
//	// 연결 성공! 이제부터 데이터 송수신 가능!
//	// ---------------------------------------
//	
//	std::cout << "Connected To Server!" << std::endl;
//
//	while (true)
//	{
//
//		char sendBuffer[100] = "Hello World!";
//		int32 resultCode = ::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
//
//		if (resultCode == INVALID_SOCKET)
//		{
//			int32 errCode = ::WSAGetLastError();
//			std::cout << "Send ErrorCode : " << errCode << std::endl;
//			return 0;
//		}
//
//		std::cout << "Send Data! Len = " << sizeof(sendBuffer) << std::endl;
//
//		char recvBuffer[1000];
//
//		int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
//		if (recvLen <= 0)
//		{
//			int32 errCode = ::WSAGetLastError();
//			std::cout << "Recv ErrorCode : " << errCode << std::endl;
//			return 0;
//		}
//
//		std::cout << "Recv Data! Data = " << recvBuffer << std::endl;
//		std::cout << "Recv Data! Len = " << recvLen << std::endl;
//
//		std::this_thread::sleep_for(1s);
//	}
//
//	// 소켓 리소스 반환
//	::closesocket(clientSocket);
//	
//	// 윈속 종료
//	::WSACleanup();
//}

//	44. 논 블로킹 소켓

//void HandleError(const char* cause)
//{
//	int32 errCode = ::WSAGetLastError();
//	std::cout << cause << " ErrorCode : " << errCode << std::endl;
//}
//
//int main()
//{
//	WSAData wsaData;
//	if(::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (clientSocket == INVALID_SOCKET)
//		return 0;
//	
//	u_long on = 1;
//	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
//		return 0;
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
//	serverAddr.sin_port = ::htons(7777);
//
//	while (true)
//	{
//		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//		{
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//			if (::WSAGetLastError() == WSAEISCONN)
//				break;
//
//			// Error
//			break;
//		}
//	}
//
//	std::cout << "Connected to Server!" << std::endl;
//
//	char sendBuffer[100] = "Hello World";
//
//	while (true)
//	{
//		if (::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0) == SOCKET_ERROR)
//		{
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//
//			break;
//		}
//
//		std::cout << "Send Data ! Len = " << sizeof(sendBuffer) << std::endl;
//
//
//		// Recv
//		while (true)
//		{
//			char recvBuffer[1000];
//			int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
//			if (recvLen == SOCKET_ERROR)
//			{
//				if (::WSAGetLastError() == WSAEWOULDBLOCK)
//					continue;
//
//				break;
//			}
//			else if (recvLen == 0)
//			{
//				break;
//			}
//
//			std::cout << "Recv Data Len = " << recvLen << std::endl;
//			break;
//		}
//
//		std::this_thread::sleep_for(1s);
//	}
//
//	// 소켓 리소스 반환
//	::closesocket(clientSocket);
//	
//	// 윈속 종료
//	::WSACleanup();
//}

//	45. Select

//void HandleError(const char* cause)
//{
//	int32 errCode = ::WSAGetLastError();
//	std::cout << cause << " ErrorCode : " << errCode << std::endl;
//}
//
//int main()
//{
//	WSAData wsaData;
//	if(::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (clientSocket == INVALID_SOCKET)
//		return 0;
//	
//	u_long on = 1;
//	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
//		return 0;
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
//	serverAddr.sin_port = ::htons(7777);
//
//	while (true)
//	{
//		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//		{
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//			if (::WSAGetLastError() == WSAEISCONN)
//				break;
//
//			// Error
//			break;
//		}
//	}
//
//	std::cout << "Connected to Server!" << std::endl;
//
//	char sendBuffer[100] = "Hello World";
//
//	while (true)
//	{
//		if (::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0) == SOCKET_ERROR)
//		{
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//
//			break;
//		}
//
//		std::cout << "Send Data ! Len = " << sizeof(sendBuffer) << std::endl;
//
//
//		// Recv
//		while (true)
//		{
//			char recvBuffer[1000];
//			int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
//			if (recvLen == SOCKET_ERROR)
//			{
//				if (::WSAGetLastError() == WSAEWOULDBLOCK)
//					continue;
//
//				break;
//			}
//			else if (recvLen == 0)
//			{
//				break;
//			}
//
//			std::cout << "Recv Data Len = " << recvLen << std::endl;
//			break;
//		}
//
//		std::this_thread::sleep_for(1s);
//	}
//
//	// 소켓 리소스 반환
//	::closesocket(clientSocket);
//	
//	// 윈속 종료
//	::WSACleanup();
//}

//	46. WSAEventSelect

//void HandleError(const char* cause)
//{
//	int32 errCode = ::WSAGetLastError();
//	std::cout << cause << " ErrorCode : " << errCode << std::endl;
//}
//
//int main()
//{
//	std::this_thread::sleep_for(1s);
//
//	WSAData wsaData;
//	if(::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (clientSocket == INVALID_SOCKET)
//		return 0;
//	
//	u_long on = 1;
//	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
//		return 0;
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
//	serverAddr.sin_port = ::htons(7777);
//
//	while (true)
//	{
//		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//		{
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//			if (::WSAGetLastError() == WSAEISCONN)
//				break;
//
//			// Error
//			break;
//		}
//	}
//
//	std::cout << "Connected to Server!" << std::endl;
//
//	char sendBuffer[100] = "Hello World";
//
//	while (true)
//	{
//		if (::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0) == SOCKET_ERROR)
//		{
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//
//			break;
//		}
//
//		std::cout << "Send Data ! Len = " << sizeof(sendBuffer) << std::endl;
//
//
//		// Recv
//		while (true)
//		{
//			char recvBuffer[1000];
//			int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
//			if (recvLen == SOCKET_ERROR)
//			{
//				if (::WSAGetLastError() == WSAEWOULDBLOCK)
//					continue;
//
//				break;
//			}
//			else if (recvLen == 0)
//			{
//				break;
//			}
//
//			std::cout << "Recv Data Len = " << recvLen << std::endl;
//			break;
//		}
//
//		std::this_thread::sleep_for(1s);
//	}
//
//	// 소켓 리소스 반환
//	::closesocket(clientSocket);
//	
//	// 윈속 종료
//	::WSACleanup();
//}

//	47. Overlapped (Event)

void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	std::cout << cause << " ErrorCode : " << errCode << std::endl;
}

int main()
{
	std::this_thread::sleep_for(1s);

	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
		return 0;

	u_long on = 1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);

	while (true)
	{
		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			if (::WSAGetLastError() == WSAEISCONN)
				break;

			// Error
			break;
		}
	}

	std::cout << "Connected to Server!" << std::endl;

	char sendBuffer[100] = "Hello World";
	WSAEVENT wsaEvent = ::WSACreateEvent();
	WSAOVERLAPPED overlapped = {};
	overlapped.hEvent = wsaEvent;

	while (true)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = sendBuffer;
		wsaBuf.len = 100;

		DWORD sendLen = 0;
		DWORD flags = 0;
		if (::WSASend(clientSocket, &wsaBuf, 1, &sendLen, flags, &overlapped, nullptr) == SOCKET_ERROR)
		{
			if (::WSAGetLastError() == WSA_IO_PENDING)
			{
				::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
				::WSAGetOverlappedResult(clientSocket, &overlapped, &sendLen, FALSE, &flags);
			}
			else
			{
				// 진짜 문제 있는 상황
				break;
			}
		}

		std::cout << "Send Data ! Len = " << sizeof(sendBuffer) << std::endl;

		std::this_thread::sleep_for(1s);
	}

	// 소켓 리소스 반환
	::closesocket(clientSocket);

	// 윈속 종료
	::WSACleanup();
}
