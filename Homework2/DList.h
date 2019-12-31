#include <iostream>
using namespace std;

template <typename T>
struct DListElement {
	T data;
	DListElement<T> *prev;
	DListElement<T> *next;
	void swapElement(DListElement<T>*&);
};

template<typename T>
void DListElement<T>::swapElement(DListElement<T>*& other)
{
	T temp = this->data;
	this->data = other->data;
	other->data = temp;
}
template <typename T>
class DList {
private:
	DListElement<T> *start;
	DListElement<T> *end;
	DListElement<T> *currentS;
	DListElement<T> *currentE;
	void deleteList();
	void copyList(DList<T> const &);
public:
	DList();
	DList(DList<T> const &);
	DList& operator= (DList<T> const &);
	~DList();
	void iterStart(DListElement<T> *elemPtr = NULL);
	DListElement<T>* iterNext();
	void iterEnd(DListElement<T> *elemPtr = NULL);
	DListElement<T>* iterPrev();
	void insertToEnd(T const &);
	void deleteElem(DListElement<T>*, T &);
	void print();
	void print_reverse();
	int length(); //може да бъде const (разглеждаме дословно реализацията)
};

template
<typename T>
DList<T>::DList() {
	start = NULL;
	end = NULL;
}
template <typename T>
DList<T>::~DList() {
	deleteList();
}
template <typename T>
DList<T>::DList(DList<T> const & list) {
	copyList(list);
}
template <typename T>
DList<T>& DList<T>::operator=(DList<T> const & list) {
	if (this != &list) {
		deleteList();
		copyList(list);
	}
	return *this;
}
template <typename T>
void DList<T>::deleteList() {
	DListElement<T> *elemPtr;
	while (start) {
		elemPtr = start;
		start = start->next;
		delete elemPtr;
	}
	end = NULL;
}
template <typename T>
void DList<T>::copyList(DList<T> const & list) {
	start = end = NULL;
	if (list.start) {
		DListElement<T> *elemPtr = list.start;
		while (elemPtr) {
			insertToEnd(elemPtr->data);
			elemPtr = elemPtr->next;
		}
	}
}
template <typename T>
void DList<T>::iterStart(DListElement<T> *elemPtr) {
	if (elemPtr) {
		currentS = elemPtr;
	}
	else {
		currentS = start;
	}
}template <typename T>
DListElement<T>* DList<T>::iterNext() {
	DListElement<T> *temp = currentS;
	if (currentS) {
		currentS = currentS->next;
	}
	return temp;
}
template <typename T>
void DList<T>::iterEnd(DListElement<T> *elemPtr) {
	if (elemPtr) {
		currentE = elemPtr;
	}
	else {
		currentE = end;
	}
}
template <typename T>
DListElement<T>* DList<T>::iterPrev() {
	DListElement<T> *temp = currentE;
	if (currentE) {
		currentE = currentE->prev;
	}
	return temp;
}
template <typename T>
void DList<T>::insertToEnd(T const & x) {
	DListElement<T> *newElemPtr = new DListElement<T>;
	newElemPtr->data = x;
	newElemPtr->next = NULL;
	if (end) {
		end->next = newElemPtr;
	}
	else {
		start = newElemPtr;
	}
	newElemPtr->prev = end;
	end = newElemPtr;
}
template <typename T>
void DList<T>::deleteElem(DListElement<T> *delElemPtr, T & x) {
	x = delElemPtr->data;
	if (start == end) {
		start = NULL;
		end = NULL;
	}
	else if (delElemPtr == start) {
		start = start->next;
		start->prev = NULL;
	}
	else if (delElemPtr == end) {
		end = delElemPtr->prev;
		end->next = NULL;
	}
	else {
		delElemPtr->prev->next = delElemPtr->next;
		delElemPtr->next->prev = delElemPtr->prev;
	}
	delete delElemPtr;
}
template <typename T>
void DList<T>::print() {
	DListElement<T>* elemPtr = start;
	while (elemPtr) {
		cout << elemPtr->data << " ";
		elemPtr = elemPtr->next;
	}
	cout << endl;
}
template <typename T>
void DList<T>::print_reverse() {
	DListElement<T>* elemPtr = end;
	while (elemPtr) {
		cout << elemPtr->data << " ";
		elemPtr = elemPtr->prev;
	}
	cout << endl;
}
template <typename T>
int DList<T>::length() {
	int n = 0;
	DListElement<T>* elemPtr = start;
	while (elemPtr) {
		n++;
		elemPtr = elemPtr->next;
	}
	return n;
}


