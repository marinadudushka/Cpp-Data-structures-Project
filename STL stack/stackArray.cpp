 #include <iostream>
using namespace std;
//stack using an array
const int MAX_SIZE = 64;
template <typename T>
class Stack
{
private:
	T arr[MAX_SIZE];
	int topIndex;//index to the top of the stack
	bool full() const; //checking if the stack is full
public:
	Stack();
	bool empty() const;
	void push(T const&);
	T pop();
	T top() const;
};

template<typename T>
bool Stack<T>::full() const
{
	return topIndex==MAX_SIZE-1;
}

template<typename T>
Stack<T>::Stack()
{
	topIndex = -1;
}

template<typename T>
bool Stack<T>::empty() const
{
	return topIndex == -1;
}

template<typename T>
void Stack<T>::push(T const & toAdd)
{
	if (full())
		cer << "stack is full!" << endl;
	else
		arr[++topIndex] = toAdd;
}

template<typename T>
T Stack<T>::pop()
{
	if (empty())
	{
		cerr << "The stack is empty";
		return T();
	}
	return arr[topIndex--];
}

template<typename T>
T Stack<T>::top() const
{
	if (empty())
	{
		cerr << "The stack is empty";
		return T();
	}
	return arr[topIndex];
}

  
