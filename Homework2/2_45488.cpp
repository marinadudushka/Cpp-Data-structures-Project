#include "DList.h"
#include <fstream>
using namespace std;
const string filename = "DLListNumbers";
void createList(DList<int> &dl)
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
		cerr << "Couldn't open file." << endl;
	int temp;
	while (!file.eof())
	{
		file >> temp;
		dl.insertToEnd(temp);
	}
	file.close();
}
void sortCocktailStyle(DList<int>& dl)
{
	bool swapped=true;
	DListElement<int>* forwardPass, *backwardPass, *currEnd, *currStart;
	dl.iterEnd();
	currEnd = dl.iterPrev();//the last element
		dl.iterStart();
	currStart = dl.iterNext();//first element
	
	while (swapped)
	{
		swapped = false;
		//front to end pass
		for (forwardPass=currStart; forwardPass != currEnd; forwardPass = forwardPass->next)//those are pointers 
		{

			if (forwardPass->data > forwardPass->next->data)
			{
				forwardPass->swapElement(forwardPass->next);
				swapped = true;
				
			}
		}
		
		if (swapped)//else nothing swapped then the list is sorted
		{
			currEnd = dl.iterPrev();//the largest number is at the end
			swapped = false;
			//back to front pass
			for (backwardPass = currEnd; backwardPass != currStart; backwardPass = backwardPass->prev)
			{
				if (backwardPass->data < backwardPass->prev->data)
				{
					swapped = true;
					backwardPass->swapElement(backwardPass->prev);
					
				}
			}
			currStart = dl.iterNext();
		}

		
	}

	
}
int main()
{
	DList<int> list;
	createList(list);
	list.iterStart();
	DListElement<int> * isEmpty = list.iterNext();
	if (!isEmpty)
		cout << "List is empty - list is sorted." << endl;
	else
	{
		cout << "List before sort: ";
		list.print();
		sortCocktailStyle(list);
		cout << "List after sort: ";
		list.print();
	}
	
	return 0;
	
}