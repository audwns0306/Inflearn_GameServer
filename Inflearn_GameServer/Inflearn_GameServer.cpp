#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>

void HelloThread()
{
	std::cout << "Hello Thread" << std::endl;
}

void HelloThread_2(int32 num)
{
	std::cout << num << std::endl;
}

int main()
{
	std::thread t;

	auto id1 = t.get_id();

	t = std::thread(HelloThread);

	std::thread t2(HelloThread_2, 10);

	int32 count = t.hardware_concurrency();		// CPU 코어 개수
	auto id = t.get_id();

	//t.detach();		// std::thread 객체에서 실제 쓰레드를 분리 즉 t로 생성된 쓰레드가 백그라운드로 알아서 남게되는


	std::cout << "Hello Main" << std::endl;

	if (t.joinable())	// t라는 객체가 살아 있는지 확인
		t.join();

	if (t2.joinable())	// t라는 객체가 살아 있는지 확인
		t2.join();

	return 0;
}
