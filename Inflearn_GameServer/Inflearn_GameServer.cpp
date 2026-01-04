#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>


//	5. 쓰레드 생성
//
//void HelloThread()
//{
//	std::cout << "Hello Thread" << std::endl;
//}
//
//void HelloThread_2(int32 num)
//{
//	std::cout << num << std::endl;
//}
//
//int main()
//{
//	std::thread t;
//
//	auto id1 = t.get_id();
//
//	t = std::thread(HelloThread);
//
//	std::thread t2(HelloThread_2, 10);
//
//	int32 count = t.hardware_concurrency();		// CPU 코어 개수
//	auto id = t.get_id();
//
//	//t.detach();		// std::thread 객체에서 실제 쓰레드를 분리 즉 t로 생성된 쓰레드가 백그라운드로 알아서 남게되는
//
//
//	std::cout << "Hello Main" << std::endl;
//
//	if (t.joinable())	// t라는 객체가 살아 있는지 확인
//		t.join();
//
//	if (t2.joinable())	// t라는 객체가 살아 있는지 확인
//		t2.join();
//
//	return 0;
//}

//	6. Atomic
//
#include <atomic>
//int32 sum = 0;
//
//void Add()
//{
//	for (int32 i = 0; i < 100'0000; ++i)
//	{
//		//sum++;
//		int32 eax = sum;
//		eax = eax + 1;
//		sum = eax;
//	}
//}
//
//void Sub()
//{
//	for (int32 i = 0; i < 100'0000; ++i)
//	{
//		//sum--;
//		int32 eax = sum;
//		eax = eax - 1;
//		sum = eax;
//	}
//}
//
//
//int main()
//{
//	Add();
//	Sub();
//	std::cout << sum << std::endl;
//
//
//}

//	7. Lock
//
#include <mutex>

//std::vector<int32> v;
//
//// Mutual Exclusive (상호배타적)
//std::mutex m;
//
//// RAII (Resource Acquisition Is Initialization)
//template<typename T>
//class LockGuard
//{
//public:
//	LockGuard(T& m)
//	{
//		_mutex = &m;
//		_mutex->lock();
//	}
//
//	~LockGuard()
//	{
//		_mutex->unlock();
//	}
//
//private:
//	T* _mutex;
//};
//
//void Push()
//{
//	for (int32 i = 0; i < 10000; ++i)
//	{
//		//LockGuard<std::mutex> lockGuard(m);
//
//		std::lock_guard<std::mutex> lockGuard(m);
//		//std::unique_lock<std::mutex> uniqueLock(m, std::defer_lock);
//
//		//uniqueLock.lock();
//
//		//m.lock();
//
//		v.push_back(i);
//		
//		//if (i == 5000)
//		//{
//		//	m.unlock();
//		//	break;
//		//}
//
//		//m.unlock();
//	}
//}
//
//int main()
//{
//	std::thread t1(Push);
//	std::thread t2(Push);
//
//	t1.join();
//	t2.join();
//
//	std::cout << v.size() << std::endl;
//}

//	8. DeadLock
//
//#include "AccountManager.h"
//#include "UserManager.h"
//
//void Func1()
//{
//	for (int32 i = 0; i < 100; ++i)
//	{
//		UserManager::Instance()->ProcessSave();
//	}
//}
//
//void Func2()
//{
//	for (int32 i = 0; i < 100; ++i)
//	{
//		AccountManager::Instance()->ProcessLogin();
//	}
//}
//
//int main()
//{
//	std::thread t1(Func1);
//	std::thread t2(Func2);
//
//	t1.join();
//	t2.join();
//
//	std::cout << "Jobs Done" << std::endl;
//}

//	10. SpinLock
//

class SpinLock {
public:
	void lock()
	{

	}

	void unlock()
	{

	}
};

std::mutex m;
int32 sum = 0;

void Add()
{
	for (int32 i = 0; i < 10'0000; ++i)
	{
		std::lock_guard<std::mutex> guard(m);
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 10'0000; ++i)
	{
		std::lock_guard<std::mutex> guard(m);
		sum--;
	}
}

int main()
{
	std::thread t1(Add);
	std::thread t2(Sub);

	t1.join();
	t2.join();
}