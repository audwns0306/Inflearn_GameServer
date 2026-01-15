#pragma once

#include <mutex>

template<typename T>
class LockStack
{
public:
	LockStack()	{}

	LockStack(const LockStack&) = delete;
	LockStack& operator=(const LockStack&) = delete;

	void Push(T value)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_stack.push(std::move(value));
		_condVar.notify_one();
	}

	bool TryPop(T& value)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		if (_stack.empty())
		{
			return false;
		}

		//	empry -> top -> pop
		value = std::move(_stack.top());
		_stack.pop();
		return true;
	}

	void WaitPop(T& value)
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_condVar.wait(lock, [this] {return _stack.empty() == false; });
		value = std::move(_stack.top());
		_stack.pop();
	}

private:
	std::stack<T> _stack;
	std::mutex _mutex;
	std::condition_variable _condVar;

};

//template<typename T>
//class LockFreeStack
//{
//	struct Node
//	{
//		Node(const T& value) : data(std::make_shared<T>(value)), next(nullptr)
//		{
//
//		}
//
//		std::shared_ptr<T> data;
//		std::shared_ptr<Node> next;
//	};
//
//public:
//
//	//	1) 새 노드를 만들고
//	//	2) 새 노드의 next = head
//	//	3) head = 새 노드
//
//	void Push(const T& value)
//	{
//		std::shared_ptr<Node> node = std::make_shared<Node>(value);
//		node->next = std::atomic_load(&_head);
//
//		/*if (_head == node->next)
//		{
//			_head = node;
//			return true;
//		}
//		else
//		{
//			node->next = _head;
//			return false;
//		}*/
//
//		while (std::atomic_compare_exchange_weak(&_head, &node->next, node) == false)
//		{
//		}
//
//		//_head = node;
//	}
//
//	//	1) head 읽기
//	//	2) head->next 읽기
//	//	3) head = head->next
//	//	4) data 추출해서 반환
//	//	5) 추출한 노드를 삭제
//
//	std::shared_ptr<T> TryPop()
//	{
//		std::shared_ptr<Node> oldHead = std::atomic_load(&_head);
//
//		while (oldHead && std::atomic_compare_exchange_weak(&_head, &oldHead, oldHead->next) == false)
//		{
//		}
//
//		if (oldHead == nullptr)
//			return std::shared_ptr<T>();
//
//		return oldHead->data;
//	}
//
//	void TryDelete(Node* oldHead)
//	{
//		if (_popCount == 1)
//		{
//			//	나 혼자
//
//			//	이왕 혼자인거, 삭제 예약된 다른 데이터들도 삭제
//			Node* node = _pendingList.exchange(nullptr);
//			
//			if (--_popCount == 0)
//			{
//				//	끼어든 애가 없음 -> 삭제 진행
//				//	이제와서 끼어들어도, 어차피 데이터는 분리해둔 상태
//				DeleteNodes(node);
//			}
//			else if (node)
//			{
//				ChainPedningNodeList(node);
//			}
//
//			//	내 데이터는 삭제
//			delete oldHead;
//		}
//		else
//		{
//			//	누가 있네? 그럼 지금 삭제하지 않고, 삭제 예약만
//			ChainPendingNode(oldHead);
//		}
//	}
//
//	void ChainPendingNodeList(Node* first, Node* last)
//	{
//		last->next = _pendingList;
//
//		while (_pendingList.compare_exchange_weak(last->next, first) == false)
//		{
//
//		}
//	}
//
//	void ChainPedningNodeList(Node* node)
//	{
//		Node* last = node;
//		while (last->next)
//		{
//			last = last->next;
//		}
//
//		ChainPendingNodeList(node, last);
//	}
//
//	void ChainPendingNode(Node* node)
//	{
//		ChainPendingNodeList(node, node);
//	}
//	
//	static void DeleteNodes(Node* node)
//	{
//		while (node)
//		{
//			Node* next = node->next;
//			delete node;
//			node = next;
//		}
//	}
//
//private:
//
//	std::shared_ptr<Node> _head;
//
//	std::atomic<uint32> _popCount = 0;	//	Pop을 실행중인 쓰레드 개수
//	std::atomic<Node*> _pendingList;	//	삭제 되어야 할 노드들 (첫번째 노드)	
//};

template<typename T>
class LockFreeStack
{
	struct Node;

	struct CountedNodePtr
	{
		int32 externalCount = 0;
		Node* ptr = nullptr;
	};

	struct Node
	{
		Node(const T& value) : data(std::make_shared<T>(value))
		{

		}

		std::shared_ptr<T> data;
		std::atomic<int32> internalCount = 0;
		CountedNodePtr next;
	};

public:
	void Push(const T& value)
	{
		CountedNodePtr node;
		node.ptr = new Node(value);
		node.externalCount = 1;
		node.ptr->next = _head;
		while (_head.compare_exchange_weak(node.ptr->next, node) == false)
		{
		}
	}

	std::shared_ptr<T> TryPop()
	{
		CountedNodePtr oldHead = _head;
		while (true)
		{
			IncreaseHeadCount(oldHead);
			Node* ptr = oldHead.ptr;
			
			//	데이터 없음
			if (ptr == nullptr)
				return std::shared_ptr<T>();

			//	소유권 획득 (ptr->next로 head를 바꿔치기 한 애가 이김)
			if (_head.compare_exchange_strong(oldHead, ptr->next))
			{
				std::shared_ptr<T> res;
				res.swap(ptr->data);

				//	external : 1 -> 2(나+1) -> 4(나+1 남+2)
				//	internal : 1 -> 0

				//	나 말고 또 누가 있는가?
				const int32 countIncrease = oldHead.externalCount - 2;

				if (ptr->internalCount.fetch_add(countIncrease) == -countIncrease)
					delete ptr;

				return res;
			}
			else if (ptr->internalCount.fetch_sub(1) == 1)
			{
				//	참조권은 얻었으나, 소유권은 실패 -> 뒷수습은 내가 한다
				delete ptr;
			}
		}
	}

private:

	void IncreaseHeadCount(CountedNodePtr& oldCounter)
	{ 
		while (true)
		{
			CountedNodePtr newCounter = oldCounter;
			newCounter.externalCount++;

			if (_head.compare_exchange_strong(oldCounter, newCounter))
			{
				oldCounter.externalCount = newCounter.externalCount;
				break;
			}
		}
	}

private:
	std::atomic<CountedNodePtr> _head;
};