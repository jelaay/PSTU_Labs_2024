#include <iostream>

struct StackElem
{
	int data;
	StackElem* next;
};

struct Stack
{
	StackElem* _top;
	int size;
	bool is_init;

	Stack(const int n) : _top(nullptr), size(0), is_init(false) { init(n); }

	void init(const int n)
	{
		if (is_init)
		{
			std::cerr << "Stack is already initialized !" << std::endl;
			return;
		}
		int data;
		for (int i = 0; i < n; ++i)
		{
			push();
		}
		is_init = true;
	}

	void print()
	{
		StackElem* cur = _top;
		while (cur != nullptr)
		{
			std::cout << cur->data << ' ';
			cur = cur->next;
		}
		std::cout << std::endl;
	}

	void push()
	{
		StackElem* cur = new StackElem;
		int data;
		std::cin >> data;
		cur->data = data;
		cur->next = _top;
		_top = cur;
		++size;
	}

	int pop()
	{
		int val = _top->data;
		StackElem* tmp = _top;
		_top = _top->next;
		--size;
		delete tmp;
		return val;
	}

	StackElem* top() { return _top; }

	~Stack()
	{
		while (_top != nullptr)
		{
			StackElem* tmp = _top;
			_top = _top->next;
			delete tmp;
			--size;
		}
	}
};

int main()
{
	return 0;
}