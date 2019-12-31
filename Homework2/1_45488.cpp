#include <iostream>
using namespace std;
struct ListNode
{
	int data;
	ListNode* next;
	ListNode(int _data):next(nullptr),data(_data){}
};
bool containsCycle(ListNode* start)
{
	ListNode* fast = start, *slow = start;
	while (fast&&fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)
			return 1;
	}
	return 0;
}
int main()
{
	//list with a cycle
	ListNode* start1;
	ListNode node11(1), node12(2), node13(3), node14(4);
	start1 = &node11;
	node11.next = &node12;
	node12.next = &node13;
	node13.next = &node14;
	node14.next = &node12;

	//list without a cycle
	ListNode* start2;
	ListNode node21(1), node22(2), node23(3), node24(4);
	start2 = &node21;
	node21.next = &node22;
	node22.next = &node23;
	node23.next = &node24;

	cout << "List one: " << containsCycle(start1)<<endl;
	cout << "List two: " << containsCycle(start2) << endl;
	
}