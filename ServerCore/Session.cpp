#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"

Session::Session()
{
	_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(_socket);
}

HANDLE Session::GetHandle()
{
	//	reinterpret_cast는 비트 그대로 해석
	//	원래라면 cast하려는 타입으로 해석하겠다는 의미
	//	그러나 여기서 사용하는 _socket의 타입은 SOCKET
	//	SOCKET은 UINT_PTR 그저 정수 타입 (포인터 크기 정수) -> 64bit면 8byte
	//	return 타입이 HANDLE이므로
	//	HANDLE로 타입만 변경한 의미
	
	return reinterpret_cast<HANDLE>(_socket);
}

void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
}
