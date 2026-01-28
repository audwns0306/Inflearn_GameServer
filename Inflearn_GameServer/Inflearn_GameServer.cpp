#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>


//	5. 쓰레드 생성

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
#include "AccountManager.h"
#include "UserManager.h"

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

//		경합이 붙어서 SpinLock이 서로 무한루프를 돌기 시작하면 CPU 점유율이 높아지는 특징이 있다.
//class SpinLock {
//public:
//	void lock()
//	{
//		// CAS (Compare-And-Swap)
//
//		bool expected = false;
//		bool desired = true;
//
//		// CAS 의사 코드
//		/*if (_locked == expected)
//		{
//			expected = _locked;
//			_locked = desired;
//			return true;
//		}
//		else
//		{
//			expected = _locked;
//			return false;
//		}*/
//
//		while (_locked.compare_exchange_strong(expected, desired) == false)
//		{
//			expected = false;
//		}
//
//	}
//
//	void unlock()
//	{
//		_locked.store(false);
//	}
//
//private:
//	std::atomic<bool> _locked = false;
//
//};
//
//std::mutex m;
//int32 sum = 0;
//SpinLock spinLock;
//
//void Add()
//{
//	for (int32 i = 0; i < 10'0000; ++i)
//	{
//		std::lock_guard<SpinLock> guard(spinLock);
//		sum++;
//	}
//}
//
//void Sub()
//{
//	for (int32 i = 0; i < 10'0000; ++i)
//	{
//		std::lock_guard<SpinLock> guard(spinLock);
//		sum--;
//	}
//}
//
//int main()
//{
//	std::thread t1(Add);
//	std::thread t2(Sub);
//
//	t1.join();
//	t2.join();
//
//	std::cout << sum << std::endl;
//
//}

//	11. Sleep
#include <chrono>

//class SpinLock {
//public:
//	void lock()
//	{
//		 CAS (Compare-And-Swap)
//
//		bool expected = false;
//		bool desired = true;
//
//		while (_locked.compare_exchange_strong(expected, desired) == false)
//		{
//			expected = false;
//
//			using namespace std::chrono_literals;
//			std::this_thread::sleep_for(std::chrono::milliseconds(100));
//			std::this_thread::sleep_for(0ms);
//			std::this_thread::yield();
//
//		}
//	}
//
//	void unlock()
//	{
//		_locked.store(false);
//	}
//
//private:
//	std::atomic<bool> _locked = false;
//
//};
//
//std::mutex m;
//int32 sum = 0;
//SpinLock spinLock;
//
//void Add()
//{
//	for (int32 i = 0; i < 10'0000; ++i)
//	{
//		std::lock_guard<SpinLock> guard(spinLock);
//		sum++;
//	}
//}
//
//void Sub()
//{
//	for (int32 i = 0; i < 10'0000; ++i)
//	{
//		std::lock_guard<SpinLock> guard(spinLock);
//		sum--;
//	}
//}
//
//int main()
//{
//	std::thread t1(Add);
//	std::thread t2(Sub);
//
//	t1.join();
//	t2.join();
//
//	std::cout << sum << std::endl;
//
//}

//	12. Event
#include <Windows.h>

//std::mutex m;
//std::queue<int32> q;
//HANDLE handle;
//
//void Producer()
//{
//	while (true)
//	{
//		{
//			std::unique_lock<std::mutex> lock(m);
//			q.push(100);
//		}
//
//		::SetEvent(handle);
//
//		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
//	}
//}
//
//void Consumer()
//{
//	while (true)
//	{
//		::WaitForSingleObject(handle, INFINITE);
//
//		std::unique_lock<std::mutex> lock(m);
//		if (q.empty() == false)
//		{
//			int32 data = q.front();
//			q.pop();
//			std::cout << data << std::endl;
//		} 
//
//	}
//}
//
//int main()
//{
//	// 커널 오브젝트
//	// Usage Count
//	// Signal / Non-Signal
//
//	handle = ::CreateEvent(NULL/*보안속성*/, FALSE/*bManualReset*/, FALSE/*bInitialState*/, NULL);
//
//	std::thread t1(Producer);
//	std::thread t2(Consumer);
//
//	t1.join();
//	t2.join();
//
//	::CloseHandle(handle);
//}

//	13. Condition Variable

//std::mutex m;
//std::queue<int32> q;
//HANDLE handle;
//
////	참고) CV는 User-Level Object (커널 오브젝트 X)
//std::condition_variable cv;
//
//void Producer()
//{
//	while (true)
//	{
//		//	1) Lock을 잡고
//		//	2) 공유 변수 값을 수정
//		//	3) Lock을 풀고
//		//	4) 조건변수 통해 다른 쓰레드에게 통지
//
//		{
//			std::unique_lock<std::mutex> lock(m);
//			q.push(100);
//		}
//
//		cv.notify_one();	//	wait중인 쓰레드가 있으면 딱 1개를 깨운다.
//
//		//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
//	}
//}
//
//void Consumer()
//{
//	while (true)
//	{
//		std::unique_lock<std::mutex> lock(m);
//		cv.wait(lock, []() { return q.empty() == false; });
//		//	1) Lock을 잡고
//		//	2) 조건 확인
//		//		- 만족O -> 빠져 나와서 이어서 코드를 진행
//		//		- 만족X -> 않으면 Lock을 풀어주고 대기 상태
//
//		//	그런데 notify_one을 했으면 항상 조건식을 만족하는거 아닐까?
//		//	Spurious Wakeup (가짜 기상?)
//		//	notify_one할 때 lock을 잡고 있는 것이 아니기 때문
//
//		if (q.empty() == false)
//		{
//			int32 data = q.front();
//			q.pop();
//			std::cout << data << std::endl;
//		}
//
//	}
//}
//
//int main()
//{
//	// 커널 오브젝트
//	// Usage Count
//	// Signal / Non-Signal
//
//	handle = ::CreateEvent(NULL/*보안속성*/, FALSE/*bManualReset*/, FALSE/*bInitialState*/, NULL);
//
//	std::thread t1(Producer);
//	std::thread t2(Consumer);
//
//	t1.join();
//	t2.join();
//
//	::CloseHandle(handle);
//}

//	14. Future
#include <future>

//int64 result;
//
//int64 Calculate()
//{
//	int64 sum = 0;
//	
//	for (int32 i = 0; i < 100'000; ++i)
//	{
//		sum += i;
//	}
//
//	result = sum;
//
//	return sum;
//}
//
//int main()
//{
//	//	동기(synchronous) 실행
//	int64 sum = Calculate();
//	std::cout << sum << std::endl;
//
//	std::thread t(Calculate);
//
//	// TODO
//
//	t.join();
//}

//	15. Cache

//	컴퓨터 구조 원리 : 캐시와 파이프라인
//	
//		CPU의 연산은 엄청 빠르나 메모리에 올라와 있는 값들을 사용하는 시간이 오래 걸린다.
//		그렇기에 CPU 내부에 캐시 장치가 존재
//		캐시 장치에도 여러 단계가 있다.	
//		레지스터 -> L1 캐시 -> L2 캐시
//		가면 갈수록 용량은 많아지나 ALU와 멀어져 접근 시간이 늘어난다.
//		캐시까지 다 뒤졌는데 데이터가 없으면 메인 메모리(RAM)으로 가서 데이터를 꺼내온다.
//		RAM에서 데이터를 꺼내올 때 다음에 혹시라도 필요할 수 있으니 캐시 어딘가에 저장해둔다.
//		동일한 데이터 혹은 인접한 데이터를 또 필요해서 사용하게 된다 가정하면
//		CPU가 캐시에서 해당 주소의 값을 먼저 들고있는지 체크한다.
// 
//	캐시 철학
//		
//		1) TEMPORAL LOCALITY
//			시간적으로 봤을 때 가장 최근에 접근한 데이터를 또 사용할 빈도가 높을 것이다.
//			라고 가정
// 
//		2) SPATIAL LOCALITY
//			공간적으로 봤을 때 옆에 있는 데이터가 또 사용할 빈도가 높을 것이다.
//			라고 가정
//			ex) for문을 통해 어떤 배열을 순차적으로 접근할 때 어떤 주소에 접근하고 바로 인접한 주소에 접근할 확률이 높기 때문에
//			
//

//int32 buffer[10000][10000];
//
//int main()
//{
//	std::memset(buffer, 0, sizeof(buffer));
//
//	{
//		uint64 start = GetTickCount64();
//
//		int64 sum = 0;
//
//		for (int32 i = 0; i < 10000; ++i)
//		{
//			for (int32 j = 0; j < 10000; ++j)
//			{
//				sum += buffer[i][j];
//			}
//		}
//
//		uint64 end = GetTickCount64();
//		std::cout <<"Elapsed Tick " << (end - start) << std::endl;
//	}
//
//	{
//		uint64 start = GetTickCount64();
//
//		int64 sum = 0;
//
//		for (int32 i = 0; i < 10000; ++i)
//		{
//			for (int32 j = 0; j < 10000; ++j)
//			{
//				sum += buffer[j][i];
//			}
//		}
//
//		uint64 end = GetTickCount64();
//		std::cout << "Elapsed Tick " << (end - start) << std::endl;
//	}
//}

//	16. CPU Pipeline

// 가시성, 코드 재배치
//int32 x = 0;
//int32 y = 0;
//int32 r1 = 0;
//int32 r2 = 0;
//
//volatile bool ready;
//
//void Thread_1()
//{
//	while (!ready)
//		;
//
//	y = 1; // Store y
//	r1 = x; // Load x
//}
//
//void Thread_2()
//{
//	while (!ready)
//		;
//
//	x = 1; // Store x
//	r2 = y; // Load x\y
//}
//
//int main()
//{
//	int32 count = 0;
//
//	while (true)
//	{
//		ready = false;
//		count++;
//
//		x = y = r1 = r2 = 0;
//
//		std::thread t1(Thread_1);
//		std::thread t2(Thread_2);
//
//		ready = true;
//
//		t1.join();
//		t2.join();
//
//		if (r1 == 0 && r2 == 0)
//		{
//			break;
//		}
//	}
//
//	std::cout << count << " 번만에 빠져나옴~" << std::endl;
//}

//	17. 메모리 관리

//std::atomic<bool> ready;
//int32 value;
//
//void Producer()
//{
//	value = 10;
//
//	ready.store(true, std::memory_order::memory_order_seq_cst);
//}
//
//void Consumer()
//{
//	while (ready.load(std::memory_order::memory_order_seq_cst) == false)
//		;
//
//	std::cout << value << std::endl;
//}
//
//int main()
//{
//	ready = false;
//	value = 0;
//	std::thread t1(Producer);
//	std::thread t2(Consumer);
//	t1.join();
//	t2.join();
//
//	//Memory Model(정책)
//	//	1) Sequentially Consistent(seq_cst)
//	//	2) Acquire - Release(consume, acquire, release, acq_rel)
//	//	3) Relaxed(relaxed)
//
//	//	1) seq_cst(가장 엄격 = 컴파일러 최적화 여지 적음 = 직관적)
//	//		가시성 문제 바로 해결, 코드 재배치 바로 해결
//	// 
//	//	2) acquire - release
//	//		딱 중간
//	//		release 명령 이전의 메모리 명령들이, 해당 명령 이후로 재배치 되는 것을 금지
//	// 
//	//	3) relaxed(자유롭다 = 컴파일러 최적화 여지 많음 = 직관적이지 않음)
//	//		너무나도 자유롭다, 코드 재배치도 멋대로 가동, 가시성 해결 X
//	//		가장 기본 조건 (동일 객체에 대한 동일 관전 순서만 보장)
//	//
//}
//
//class Knight {
//
//	int32 hp;
//	int32 mp;
//
//public:
//	Knight() :  hp(5), mp(6) {
//
//	}
//};
//
//std::atomic<bool> flag;
//
//int main()
//{
//	flag = false;
//
//	//flag = true;
//	flag.store(true, std::memory_order::memory_order_seq_cst);
//
//	//bool val = flag;
//	bool val = flag.load(std::memory_order::memory_order_seq_cst);
//
//	//	이전 flag 값을 prev에 넣고, flag 값을 수정
//	{
//		bool prev = flag.exchange(true);
//		/*bool prev = flag;
//		flag = true;*/
//	}
//
//	{
//		bool expected = false;
//		bool desired = true;
//		flag.compare_exchange_strong(expected, desired);
//	}
//
//	{
//		std::atomic<int64> v;
//		std::cout << v.is_lock_free() << std::endl;
//	}
//
//	{
//		std::atomic<Knight> v;
//		std::cout << v.is_lock_free() << std::endl;
//	}
//}

//	18. Thread Local Storage

//	TLS는 쓰레드별로 본인만 가지는 저장소
//	Heap 영역과	Data 영역은 쓰레드 끼리 공유가 가능하지만 TLS는 불가능
//	스택과 TLS가 다른게 뭐냐
//	스택은 함수를 위한 메모리 공간

//using namespace std::chrono_literals;
//
//thread_local int32 LThreadId = 0;
//
//
//void ThreadMain(int32 threadId)
//{
//	LThreadId = threadId;
//
//	while (true)
//	{
//
//		std::cout << "Hi! I am Thread " << LThreadId << std::endl;
//		std::this_thread::sleep_for(1s);
//	}
//}
//
//int main()
//{
//	std::vector<std::thread> threads;
//
//	for (int32 i = 0; i < 10; ++i)
//	{
//		int32 threadId = i + 1;
//		threads.push_back(std::thread(ThreadMain, threadId));
//	}
//
//	for (std::thread& t : threads)
//	{
//		t.join();
//	}
//}

//	19. Lock-Based Stack / Queue
#include "ConcurrentQueue.h"
#include "ConcurrentStack.h"

//
//using namespace std::chrono_literals;
//
//LockQueue<int32> q;
//LockStack<int32> s;
//
//void Push()
//{
//	while (true)
//	{
//		int32 value = rand() % 100;
//		q.Push(value);
//
//		std::this_thread::sleep_for(10ms);
//	}
//}
//
//void Pop()
//{
//	while (true)
//	{
//		int32 data = 0;
//		if (q.TryPop(OUT data))
//			std::cout << data << std::endl;
//	}
//}
//
//int main()
//{
//	std::thread t1(Push);
//	std::thread t2(Pop);
//	std::thread t3(Pop);
//
//	t1.join();
//	t2.join();
//}

//	20~22. Lock-Free Stack

//using namespace std::chrono_literals;
//
//LockQueue<int32> q;
//LockFreeStack<int32> s;
//
//void Push()
//{
//	while (true)
//	{
//		int32 value = rand() % 100;
//		s.Push(value);
//
//		/*std::this_thread::sleep_for(10ms);*/
//	}
//}
//
//void Pop()
//{
//	while (true)
//	{
//		auto data = s.TryPop();
//		if(data!=nullptr)
//		{
//			std::cout << (*data) << std::endl;
//		}
//	}
//}
//
//int main()
//{
//	std::shared_ptr<int32> ptr;
//	bool value = std::atomic_is_lock_free(&ptr);
//
//	std::thread t1(Push);
//	std::thread t2(Pop);
//	std::thread t3(Pop);
//
//	t1.join();
//	t2.join();
//	t3.join();
//}

//	24. ThreadManager
#include "ThreadManager.h"

//CoreGlobal Core;
//
//using namespace std::chrono_literals;
//
//void ThreadMain()
//{
//	while (true)
//	{
//		std::cout << "Hello ! I am Thread... " << LThreadId << std::endl;
//		std::this_thread::sleep_for(1s);
//	}
//}
//
//int main()
//{
//	for (int32 i = 0; i < 5; ++i)
//	{
//		GThreadManager->Launch(ThreadMain);
//	}
//
//	GThreadManager->Join();
//}

//	28. Reference Counting
#include "RefCounting.h"

//class Wraight : public RefCountable
//{
//public:
//	int _hp = 150;
//	int _posX = 0;
//	int _posY = 0;
//};
//
//using WraightRef = TSharedPtr<Wraight>;
//
//class Missile : public RefCountable
//{
//public:
//	void SetTarget(WraightRef target)
//	{
//		_target = target;
//		//target->AddRef();
//		Test(target);
//	}
//	//	참조하게 되면 RefCount 증가 X
//	void Test(WraightRef& target)
//	{
//
//	}
//
//	bool Update()
//	{
//		if (_target == nullptr)
//			return true;
//
//		int posX = _target->_posX;
//		int posY = _target->_posY;
//
//		if (_target->_hp == 0)
//		{
//			_target->ReleaseRef();
//			_target = nullptr;
//			return true;
//		}
//
//		return false;
//	}
//
//	WraightRef _target = nullptr;
//};
//
//
//using MissileRef = TSharedPtr<Missile>;
//
//int main()
//{
//	WraightRef wraight(new Wraight());
//	wraight->ReleaseRef();
//	MissileRef missile(new Missile());
//	missile->ReleaseRef();
//
//	missile->SetTarget(wraight);
//
//	// 레이스가 피격 당함
//	wraight->_hp = 0;
//	//wraight->ReleaseRef();
//	wraight = nullptr;
//
//	while (true)
//	{
//		if (missile->Update())
//		{
//			missile->ReleaseRef();
//			missile = nullptr;
//		}
//	}
//
//}

//	29. Smart Pointer

//int main()
//{
//	
//	//	우리가 만든 SharedPtr방식의 한계
//	// 
//	//	1) 이미 만들어진 클래스 대상으로 사용 불가
//	//	2) 순환 (Cycle) 문제
//}

//	30.	Allocator

//int main()
//{
//
//}

//	38~40. 소켓 프로그래밍
#include <WinSock2.h>
#include <MSWSock.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

//int main()
//{
//	WSAData wsaData;
//	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	// ad : Address Family (AF_INET = IPv4, AF_INET6 = IPv6)
//	// type : TCP(SOCK_STREAM) vs UDP(SOCK_DGRAM)
//	// protocol : 0
//	// return : descriptor
//
//	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (listenSocket == INVALID_SOCKET)
//	{
//		int32 errCode = ::WSAGetLastError();
//		std::cout << "Socket ErrorCode : " << errCode << std::endl;
//		return 0;
//	}
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
//	serverAddr.sin_port = ::htons(7777);
//
//	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//	{
//		int32 errCode = ::WSAGetLastError();
//		std::cout << "Bind ErrorCode : " << errCode << std::endl;
//		return 0;
//	}
//
//	if(::listen(listenSocket, 10))
//	{
//		int32 errCode = ::WSAGetLastError();
//		std::cout << "Listen ErrorCode : " << errCode << std::endl;
//		return 0;
//	}
//
//	// --------------------------
//	
//	while (true)
//	{
//		SOCKADDR_IN clientAddr;
//		::memset(&clientAddr, 0, sizeof(clientAddr));
//		int32 addrLen = sizeof(clientAddr);
//
//		SOCKET clientSocket = ::accept(listenSocket,(SOCKADDR*)&clientAddr, &addrLen);
//		if (clientSocket == INVALID_SOCKET)
//		{
//			int32 errCode = ::WSAGetLastError();
//			std::cout << "Accept ErrorCode : " << errCode << std::endl;
//			return 0;
//		}
//
//		char ipAddr[16];
//		::inet_ntop(AF_INET, &clientAddr, ipAddr, sizeof(ipAddr));
//
//		std::cout << "Client Connected! IP = " << ipAddr << std::endl;
//		
//		
//
//		while (true)
//		{
//			char recvBuffer[1000];
//
//			int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
//			if (recvLen <= 0)
//			{
//				int32 errCode = ::WSAGetLastError();
//				std::cout << "Recv ErrorCode : " << errCode << std::endl;
//				return 0;
//			}
//
//			std::cout << "Recv Data! Data = " << recvBuffer << std::endl;
//			std::cout << "Recv Data! Len = " << recvLen << std::endl;
//
//			int32 resultCode = ::send(clientSocket, recvBuffer, recvLen, 0);
//
//			if (resultCode == INVALID_SOCKET)
//			{
//				int32 errCode = ::WSAGetLastError();
//				std::cout << "Send ErrorCode : " << errCode << std::endl;
//				return 0;
//			}
//
//		}
//	}
//
//	// --------------------------
//	::WSACleanup();
//}

//	43.	소켓 옵션

//void HandleError(const char* cause)
//{
//	int32 errCode = ::WSAGetLastError();
//	std::cout << cause << " ErrorCode : " << errCode << std::endl;
//}
//
//int main()
//{
//	WSAData wsaData;
//	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET serverSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (serverSocket == INVALID_SOCKET)
//	{
//		HandleError("Socket");
//		return 0;
//	}
//
//
//	// 옵션을 해석하고 처리할 주체?
//	// 소켓 코드 -> SOL_SOCKET
//	// IPv4 -> IPPROTO_IP
//	// TCP 프로토콜 -> IPPROTO_TCP
//
//	// SO_KEEPALIVE = 주기적으로 연결 상태 확인 여부 (TCP Only)
//	// 상대방이 소리소문없이 연결 끊는다면?
//	// 주기적으로 TCP 프로토콜 연결 상태 확인 -> 끊어진 연결 감지
//	bool enable = true;
//	::setsockopt(serverSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&enable, sizeof(enable));
//
//	// SO_LINGER = 지연하다
//	// 송신 버퍼에 있는 데이터를 보낼 것인가? 날릴 것인가?
//	// onoff = 0이면 closesocket()이 바로 리턴, 아니면 linger초만큼 대기 (default 0)
//	// linger = 대기 시간
//	LINGER linger;
//	linger.l_onoff = 1;
//	linger.l_linger = 5;
//	::setsockopt(serverSocket, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));
//
//	// Half-Close
//	// SD_SEND : send 막는다
//	// SD_RECEIVE : recv 막는다
//	// SD_BOTH : 둘다 막는다
//	//::shutdown(serverSocket, SD_SEND);
//
//	// SO_SNDBUF = 송신 버퍼 크기
//	// SO_RCVBUF = 수신 버퍼 크기
//	int32 sendBufferSize;
//	int32 optionLen = sizeof(sendBufferSize);
//	::getsockopt(serverSocket, SOL_SOCKET, SO_SNDBUF, (char*)&sendBufferSize, &optionLen);
//	std::cout << "송신 버퍼 크기 : " << sendBufferSize << std::endl;
//
//	int32 recvBufferSize;
//	optionLen = sizeof(recvBufferSize);
//	::getsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, (char*)&recvBufferSize, &optionLen);
//	std::cout << "수신 버퍼 크기 : " << recvBufferSize << std::endl;
//
//	// SO_REUSEADDR
//	// IP주소 및 port 재사용
//	{
//		bool enable = true;
//		::setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(enable));
//	}
//
//	// IPPROTO_TCP
//	// TCP_NODELAY = Nagle 네이글 알고리즘 작동 여부
//	// 데이터가 충분히 크면 보내고, 그렇지 않으면 데이터가 충분히 쌓일때까지 대기
//	// 장점 : 작은 패킷이 불필요하게 많이 생성되는 일을 방지
//	// 단점 : 반응 시간 손해
//	// 일반적으로 NODELAY를 키면서 Nagle을 끈다
//	{
//		bool enable = true;
//		::setsockopt(serverSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&enable, sizeof(enable));
//	}
//
//	::closesocket(serverSocket);
//
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
//	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (listenSocket == INVALID_SOCKET)
//		return 0;
//
//	u_long on = 1;
//	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)
//		return 0;
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
//	serverAddr.sin_port = htons(7777);
//
//	if(::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//		return 0;
//
//	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
//		return 0;
//
//	std::cout << "Accept" << std::endl;
//
//	SOCKADDR_IN clientAddr;
//	int32 addrLen = sizeof(clientAddr);
//
//	while (true)
//	{
//		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
//		if (clientSocket == INVALID_SOCKET)
//		{
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//
//			break;
//		}
//
//		std::cout << "Client Connected!" << std::endl;
//
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
//
//			// Send
//			while (true)
//			{
//				if (::send(clientSocket, recvBuffer, recvLen, 0) == SOCKET_ERROR)
//				{
//					if (::WSAGetLastError() == WSAEWOULDBLOCK)
//						continue;
//
//					break;
//				}
//
//				std::cout << "Send Data ! Len = " << recvLen << std::endl;
//				break;
//			}
//		}
//	}
//
//	::WSACleanup();
//}

//	45. Select

//const int32 BUFSIZE = 1000;
//
//struct Session
//{
//	SOCKET socket = INVALID_SOCKET;
//	char recvBuffer[BUFSIZE] = {};
//	int32 recvBytes = 0;
//	int32 sendBytes = 0;
//};
//
//int main()
//{
//	WSAData wsaData;
//	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (listenSocket == INVALID_SOCKET)
//		return 0;
//
//	u_long on = 1;
//	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)
//		return 0;
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
//	serverAddr.sin_port = htons(7777);
//
//	if(::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//		return 0;
//
//	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
//		return 0;
//
//	std::cout << "Accept" << std::endl;
//
//	std::vector<Session> sessions;
//	sessions.reserve(100);
//
//	fd_set reads;
//	fd_set writes;
//
//	while (true)
//	{
//		// 소켓 셋 초기화
//		FD_ZERO(&reads);
//		FD_ZERO(&writes);
//
//		// ListenSocket 등록
//		FD_SET(listenSocket, &reads);
//
//		// 소켓 등록
//		for (Session& s : sessions)
//		{
//			if (s.recvBytes <= s.sendBytes)
//				FD_SET(s.socket, &reads);
//			else
//				FD_SET(s.socket, &writes);
//		}
//
//		// [옵션] 마지막 timeout 인자 설정 가능
//		int32 retVal = ::select(0, &reads, &writes, nullptr, nullptr);
//		if (retVal == SOCKET_ERROR)
//			break;
//
//		// Listener 소켓 체크
//		if (FD_ISSET(listenSocket, &reads))
//		{
//			SOCKADDR_IN clientAddr;
//			int32 addrLen = sizeof(clientAddr);
//			SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
//			if (clientSocket != INVALID_SOCKET)
//			{
//				std::cout << "Client Connected" << std::endl;
//				sessions.push_back(Session{ clientSocket });
//			}
//		}
//
//		// 나머지 소켓 체크
//		for (Session& s : sessions)
//		{
//			// Read
//			if (FD_ISSET(s.socket, &reads))
//			{
//				int32 recvLen = ::recv(s.socket, s.recvBuffer, BUFSIZE, 0);
//				if (recvLen <= 0)
//				{
//					// TODO : sessions 제거
//					continue;
//				}
//
//				s.recvBytes = recvLen;
//			}
//
//			// Write
//			if (FD_ISSET(s.socket, &writes))
//			{
//				// 블로킹 모드 -> 모든 데이터 다 보냄
//				// 논블로킹 모드 -> 일부만 보낼 수가 있음 ( 상대방 수신 버퍼 상황에 따라 )
//				int32 sendLen = ::send(s.socket, &s.recvBuffer[s.sendBytes], s.recvBytes - s.sendBytes, 0);
//				if (sendLen == SOCKET_ERROR)
//				{
//					continue;
//				}
//
//				s.sendBytes += sendLen;
//				if (s.recvBytes == s.sendBytes)
//				{
//					s.recvBytes = 0;
//					s.sendBytes = 0;
//				}
//			}
//		}
//	}
//
//	::WSACleanup();
//}

//	46. WSAEventSelect

//const int32 BUFSIZE = 1000;
//
//struct Session
//{
//	SOCKET socket = INVALID_SOCKET;
//	char recvBuffer[BUFSIZE] = {};
//	int32 recvBytes = 0;
//	int32 sendBytes = 0;
//};
//
//int main()
//{
//	WSAData wsaData;
//	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (listenSocket == INVALID_SOCKET)
//		return 0;
//
//	u_long on = 1;
//	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)
//		return 0;
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
//	serverAddr.sin_port = htons(7777);
//
//	if(::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//		return 0;
//
//	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
//		return 0;
//
//	std::cout << "Accept" << std::endl;
//
//	// WSAEventSelect = (WSAEventSelect 함수가 핵심이 되는)
//	// 소켓과 관련된 네트워크 이벤트를 [이벤트 객체]를 통해 감지
//
//	// 이벤트 객체 관련 함수들
//	// 생성 : WSACreateEvent (수동 리셋 Manual-Reset + Non-Signaled 상태 시작)
//	// 삭제 : WSACloseEvent
//	// 신호 상태 감지 : WSAWaitForMultipleEvents
//	// 구체적인 네트워크 이벤트 알아내기 : WSAEnumNetworkEvents
//
//	// 소켓 <-> 이벤트 객체 연동
//	// WSAEventSelect(socket, event, networkEvents);
//	// - 관심있는 네트워크 이벤트
//	// FD_ACCEPT : 접속한 클라가 있음 accept
//	// FD_READ : 데이터 수신 가능 recv, recvfrom
//	// FD_WRITE : 데이터 송신 가능 send, sendto
//	// FD_CLOSE : 상대가 접속 종료
//	// FD_CONNECT : 통신을 위한 연결 절차 완료
//	// FD_OOB
//
//	// 주의 사항
//	// WSAEventSelect 함수를 호출하면, 해당 소켓은 자동으로 넌블로킹 모드 전환
//	// accept() 함수가 리턴하는 소켓은 listenSocket과 동일한 속성을 갖는다
//	// - 따라서 clientSocket은 FD_READ, FD_WRITE 등을 다시 등록 필요
//	// - 드물게 WSAEWOULDBLOCK 오류가 뜰 수 있으니 예외 처리 필요
//	// 중요)
//	// - 이벤트 발생 시, 적절한 소켓 함수 호출해야 함
//	// - 아니면 다음 번에는 동일 네트워크 이벤트가 발생 X
//	// ex) FD_READ 이벤트 떴으면 recv() 호출해야 하고, 안하면 FD_READ 두 번 다시 X
//
//	// 1) count, event
//	// 2) waitAll : 모두 기다림? 하나만 완료 되어도 OK?
//	// 3) timeout : 타임아웃
//	// 4) 지금은 false
//	// return : 완료된 첫번째 인덱스
//	// WSAWaitForMultipleEvents
//
//	// 1) socket
//	// 2) eventObject : socket 과 연동된 이벤트 객체 핸들을 넘겨주면, 이벤트 객체를 non-signaled
//	// 3) networkEvent : 네트워크 이벤트 / 오류 정보가 저장
//	// WSAEnumNetworkEvents
//
//	std::vector<WSAEVENT> wsaEvents;
//	std::vector<Session> sessions;
//	sessions.reserve(100);
//
//	WSAEVENT listenEvent = ::WSACreateEvent();
//	wsaEvents.push_back(listenEvent);
//	sessions.push_back(Session{ listenSocket });
//	if (::WSAEventSelect(listenSocket, listenEvent, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR)
//		return 0;
//
//	while (true)
//	{
//		int32 index = ::WSAWaitForMultipleEvents(wsaEvents.size(), &wsaEvents[0], FALSE, WSA_INFINITE, FALSE);
//		if (index == WSA_WAIT_FAILED)
//			continue;
//		
//		index -= WSA_WAIT_EVENT_0;
//
//		WSANETWORKEVENTS networkEvents;
//		if (::WSAEnumNetworkEvents(sessions[index].socket, wsaEvents[index], &networkEvents) == SOCKET_ERROR)
//			continue;
//
//		// Listener 소켓 체크
//		if (networkEvents.lNetworkEvents & FD_ACCEPT)
//		{
//			// Error-Check
//			if (networkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
//				continue;
//
//			SOCKADDR_IN clientAddr;
//			int32 addrLen = sizeof(clientAddr);
//
//			SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
//			if (clientSocket != INVALID_SOCKET)
//			{
//				std::cout << "Client Connected" << std::endl;
//
//				WSAEVENT clientEvent = ::WSACreateEvent();
//				wsaEvents.push_back(listenEvent);
//				sessions.push_back(Session{ listenSocket });
//				if (::WSAEventSelect(clientSocket, clientEvent, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
//					return 0;
//			}
//		}
//
//		// Client Session 소켓 체크
//		if (networkEvents.lNetworkEvents & FD_READ || networkEvents.lNetworkEvents & FD_WRITE)
//		{
//			if ((networkEvents.lNetworkEvents & FD_READ) && (networkEvents.iErrorCode[FD_READ_BIT] != 0))
//				continue;
//			if ((networkEvents.lNetworkEvents & FD_WRITE) && (networkEvents.iErrorCode[FD_WRITE_BIT] != 0))
//				continue;
//
//			Session& s = sessions[index];
//
//			// Read
//			if (s.recvBytes == 0)
//			{
//				int32 recvLen = ::recv(s.socket, s.recvBuffer, BUFSIZE, 0);
//				if (recvLen == SOCKET_ERROR && ::WSAGetLastError() != WSAEWOULDBLOCK)
//					continue;
//			
//				s.recvBytes = recvLen;
//				std::cout << "Recv Data = " << recvLen << std::endl;
//			}
//
//			if (s.recvBytes > s.sendBytes)
//			{
//				int32 sendLen = ::send(s.socket, &s.recvBuffer[s.sendBytes], s.recvBytes - s.sendBytes, 0);
//				if (sendLen == SOCKET_ERROR && ::WSAGetLastError() != WSAEWOULDBLOCK)
//				{
//					continue;
//				}
//
//				s.sendBytes += sendLen;
//				if (s.recvBytes == s.sendBytes)
//				{
//					s.recvBytes = 0;
//					s.sendBytes = 0;
//				}
//
//				std::cout << "Send Data = " << sendLen << std::endl;
//			}
//		}
//
//		// FD_CLOSE 처리
//		if (networkEvents.lNetworkEvents & FD_CLOSE)
//		{
//			// TODO : Remove Socket
//		}
//	}
//
//	::WSACleanup();
//}

//	47. Overlapped (Event)

// Blocking VS Non-Blocking
// - 함수를 호출하면 대기하는지? 바로 완료되는지?
// 
// Synchronous(동기) VS Asynchronous(비동기)
// - 지금까지 사용한 send, recv는 Synchronous 함수


//const int32 BUFSIZE = 1000;
//
//struct Session
//{
//	SOCKET socket = INVALID_SOCKET;
//	char recvBuffer[BUFSIZE] = {};
//	int32 recvBytes = 0;
//	WSAOVERLAPPED overlapped = {};
//};
//
//int main()
//{
//	WSAData wsaData;
//	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (listenSocket == INVALID_SOCKET)
//		return 0;
//
//	u_long on = 1;
//	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)
//		return 0;
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
//	serverAddr.sin_port = htons(7777);
//
//	if(::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//		return 0;
//
//	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
//		return 0;
//
//	std::cout << "Accept" << std::endl;
//
//	// Overlapped IO (비동기 + 논블로킹)
//	// - Overlapped 함수를 건다 (WSARecv, WSASend)
//	// - Overlapped 함수가 성공했는지 확인을 한 후
//	// -> 성공했으면 결과 얻어서 처리
//	// -> 실패했으면 사유를 확인
//
//
//	// 1) 비동기 입출력 소켓
//	// 2) WSABUF 배열의 시작 주소 + 개수
//	// 3) 보내고/받은 바이트 수
//	// 4) 상세 옵션인데 0
//	// 5) WSAOVERLAPPED 구조체 주소값
//	// 6) 입출력이 완료되면 OS가 호출할 콜백 함수
//	// WSASend
//	// WSARecv
//	// Scatter-Gather
//
//	// Overlapped (이벤트 기반)
//	// - 비동기 입출력 지원하는 소켓 생성 + 통지 받기 위한 이벤트 객체 생성
//	// - 비동기 입출력 함수 호출 (1에서 만든 이벤트 객체를 같이 넘겨줌)
//	// - 비동기 작업이 바로 완료되지 않으면, WSA_IO_PENDING 오류 코드
//	// 운영체제는 이벤트 객체를 signaled 상태로 만들어서 완료 상태 알려줌
//	// - WSAWaitForMultipleEvents 함수 호출해서 이벤트 객체의 signal 판별
//	// - WSAGetOverlappedResult 호출해서 비동기 입출력 결과 확인 및 데이터 처리
//
//	// 1) 비동기 소켓
//	// 2) 넘겨준 overlapped 구조체
//	// 3) 전송된 바이트 수
//	// 4) 비동기 입출력 작업이 끝날때까지 대기할지?
//	// false
//	// 5) 비동기 입출력 작업 관련 부가 정보. 거의 사용 안 함.
//	// WSAGetOverlappedResult
//
//	while (true)
//	{
//		SOCKADDR_IN clientAddr;
//		int32 addrLen = sizeof(clientAddr);
//
//		SOCKET clientSocket;
//		while (true)
//		{
//			clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
//			if (clientSocket != INVALID_SOCKET)
//				break;
//
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//
//			return 0;
//		}
//
//		Session session = Session{ clientSocket };
//		WSAEVENT wsaEvent = ::WSACreateEvent();
//		session.overlapped.hEvent = wsaEvent;
//
//		std::cout << "Client Connected !" << std::endl;
//
//		while (true)
//		{
//			WSABUF wsaBuf;
//			wsaBuf.buf = session.recvBuffer;
//			wsaBuf.len = BUFSIZE;
//
//			DWORD recvLen = 0;
//			DWORD flags = 0;
//			if (::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &session.overlapped, nullptr) == SOCKET_ERROR)
//			{
//				if (::WSAGetLastError() == WSA_IO_PENDING)
//				{
//					// Pending
//					::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
//					::WSAGetOverlappedResult(session.socket, &session.overlapped, &recvLen, FALSE, &flags);
//				}
//				else
//				{
//					// TODO : 문제 있는 상황
//					break;
//				}
//			}
//
//			std::cout << "Data Recv Len = " << recvLen << std::endl;
//		}
//		::closesocket(session.socket);
//	}
//
//	::WSACleanup(); 
//}

//	48. Overlapped (Call-Back)

//const int32 BUFSIZE = 1000;
//
//struct Session
//{
//	SOCKET socket = INVALID_SOCKET;
//	char recvBuffer[BUFSIZE] = {};
//	int32 recvBytes = 0;
//	WSAOVERLAPPED overlapped = {};
//};
//
//void CALLBACK RecvCallback(DWORD error, DWORD recvLen, LPWSAOVERLAPPED overlapps, DWORD flags)
//{
//	std::cout << "Data Recv Len Callback = " << recvLen << std::endl;
//	// TODO : echo 서버를 만든다면 WSASend()
//}
//
//int main()
//{
//	WSAData wsaData;
//	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		return 0;
//
//	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (listenSocket == INVALID_SOCKET)
//		return 0;
//
//	u_long on = 1;
//	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)
//		return 0;
//
//	SOCKADDR_IN serverAddr;
//	::memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
//	serverAddr.sin_port = htons(7777);
//
//	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//		return 0;
//
//	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
//		return 0;
//
//	std::cout << "Accept" << std::endl;
//
//	// Overlapped (Completion Routine 콜백 기반)
//	// - 비동기 입출력 지원하는 소켓 생성
//	// - 비동기 입출력 함수 호출 (완료 루틴의 시작 주소를 넘겨준다)
//	// - 비동기 작업이 바로 완료되지 않으면, WSA_IO_PENDING 오류 코드
//	// - 비동기 입출력 함수 호출한 쓰레드를 -> Alertable Wait 상태로 만든다
//	// ex) WaitForSingleObjectEx, WaitForMultipleObjectsEx, SleepEx, WSAWaitForMultipleEvents
//	// - 비동기 IO 완료되면, 운영체제는 완료 루틴 호출
//	// - 완료 루틴 호출이 모두 끝나면, 쓰레드는 Alertable Wait 상태에서 빠져나온다.
//	
//	// 1) 오류 발생시 0 아닌 값
//	// 2) 전송 바이트 수
//	// 3) 비동기 입출력
//	//
//	// void CompletionRoutine()
//
//	while (true)
//	{
//		SOCKADDR_IN clientAddr;
//		int32 addrLen = sizeof(clientAddr);
//
//		SOCKET clientSocket;
//		while (true)
//		{
//			clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
//			if (clientSocket != INVALID_SOCKET)
//				break;
//
//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
//				continue;
//
//			return 0;
//		}
//
//		Session session = Session{ clientSocket };
//		WSAEVENT wsaEvent = ::WSACreateEvent();
//
//		std::cout << "Client Connected !" << std::endl;
//
//		while (true)
//		{
//			WSABUF wsaBuf;
//			wsaBuf.buf = session.recvBuffer;
//			wsaBuf.len = BUFSIZE;
//
//			DWORD recvLen = 0;
//			DWORD flags = 0;
//			if (::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &session.overlapped, RecvCallback) == SOCKET_ERROR)
//			{
//				if (::WSAGetLastError() == WSA_IO_PENDING)
//				{
//					// Pending
//					// Alertable Wait
//					::SleepEx(INFINITE, TRUE);
//					//::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
//				}
//				else
//				{
//					// TODO : 문제 있는 상황
//					break;
//				}
//			}
//			else
//			{
//			std::cout << "Data Recv Len = " << recvLen << std::endl;
//			}
//		}
//		::closesocket(session.socket);
//	}
//
//	::WSACleanup();
//}

//	49. Completion Port (IOCP)

const int32 BUFSIZE = 1000;

struct Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BUFSIZE] = {};
	int32 recvBytes = 0;
};

enum IO_TYPE
{
	READ,
	WRITE,
	ACCEPT,
	CONNECT,
};

struct OverlappedEx
{
	WSAOVERLAPPED overlapped = {};
	int32 type = 0;	// read, write, accept, connect ...
};

void WorkerThreadMain(HANDLE iocpHandle)
{
	while (true)
	{
		DWORD bytesTransferred = 0;
		Session* session = nullptr;
		OverlappedEx* overlappedEx = nullptr;

		BOOL ret = ::GetQueuedCompletionStatus(iocpHandle, &bytesTransferred, (ULONG_PTR*)&session, (LPOVERLAPPED*)&overlappedEx, INFINITE);

		if (ret == FALSE || bytesTransferred == 0)
		{
			// TODO : 연결 끊김
			continue;
		}

		// 여기서 switch를 이용해 어떤걸 할지 결정한다.
		ASSERT_CRASH(overlappedEx->type == IO_TYPE::READ);

		std::cout << "Recv Data IOCP = " << bytesTransferred << std::endl;



		WSABUF wsaBuf;
		wsaBuf.buf = session->recvBuffer;
		wsaBuf.len = BUFSIZE;

		DWORD recvLen = 0;
		DWORD flags = 0;
		::WSARecv(session->socket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);

	}
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = htons(7777);

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		return 0;

	std::cout << "Accept" << std::endl;

	// Overlapped (Completion Routine 콜백 기반)
	// - 비동기 입출력 함수 완료되면, 쓰레드마다 있는 APC 큐에 일감이 쌓임
	// - Alertable Wait 상태로 들어가서 APC 큐 비우기 (콜백 함수)
	// 단점) APC 큐 쓰레드마다 있다!

	// IOCP (Completion Port) 모델
	// - APC -> Completion Port (쓰레드마다 있는건 아니고 1개. 중앙에서 관리하는 APC 큐?)
	// - Alertable Wait -> CP 결과 처리를 GetQueuedCompletionStatus
	// 쓰레드랑 궁합이 굉장히 좋다!

	// CreateIoCompletionPort
	// GetQueuedCompletionStatus

	std::vector<Session*> sessionManager;

	// CP 생성
	HANDLE iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	
	// WorkerThreads
	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch([=]() {WorkerThreadMain(iocpHandle); });
	}

	// Main Thread = Accept 담당
	while (true)
	{
		SOCKADDR_IN clientAddr;
		int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
			return 0;

		Session* session = new Session();
		session->socket = clientSocket;
		sessionManager.push_back(session);

		std::cout << "Client Connected !" << std::endl;

		// 소켓을 CP에 등록 (관찰 대상이라는걸 알려준다.)
		::CreateIoCompletionPort((HANDLE)clientSocket, iocpHandle, /*Key*/(ULONG_PTR)session, 0);

		WSABUF wsaBuf;
		wsaBuf.buf = session->recvBuffer;
		wsaBuf.len = BUFSIZE;

		OverlappedEx* overlappedEx = new OverlappedEx();
		overlappedEx->type = IO_TYPE::READ;

		DWORD recvLen = 0;
		DWORD flags = 0;
		::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);

		//::closesocket(session.socket);
	}

	GThreadManager->Join();

	::WSACleanup();
}