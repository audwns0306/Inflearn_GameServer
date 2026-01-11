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

#include "AccountManager.h"
#include "UserManager.h"
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
//		경합이 붙어서 SpinLock이 서로 무한루프를 돌기 시작하면 CPU 점유율이 높아지는 특징이 있다.

//
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
//
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
//
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
//

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
//
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
//

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
//

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
//

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
//

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
//

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

//	20. Lock-Free Stack
//


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
//		int32 data = 0;
//		if (s.TryPop(OUT data))
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
//	t3.join();
//}
