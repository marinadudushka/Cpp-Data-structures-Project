#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;
unsigned int m(unsigned int x, unsigned int y)// min of x and y
{
	return x < y ? x : y;
}
unsigned int fact(unsigned int x) // recursive factorial helper function
{
	if (x == 1||x==0)
		return 1;
	return x * fact(x - 1);
}
unsigned int f(unsigned int x)
{
	return (x*x) % 100;

}
unsigned int g(int x)//check if same
{
	x = fact(x % 5);
	return x;
}

void getResults(ifstream & file)//file opened at the begining 
{
	 int equations;
	file >> equations;
	file.get();
	if (equations < 0)
	{
		cerr << "Not enough equations!";
	}
	else
	{	
		for (int i = 0; i < equations; i++)
		{
			stack<char> functionStack;
			stack<unsigned int> numberStack;
			string fileline, equatNum="";
			getline(file,fileline);
			int len = fileline.length();
			char c;
			for (int j = 0; j < len; j++)
			{
				c = fileline[j];
				if (c == 'f' || c == 'g' || c == 'm' || c == '('|| c == ',' || c == ')')
				{
					if (c == ',' || c == ')')
					{
						if (equatNum != "")
						{
							int temp = stoi(equatNum);
							numberStack.push(temp);
							equatNum = "";
						}
					}
					if(c!=')')
						functionStack.push(c);
				}
				if (c == ')')
				{
					unsigned int res;
					char temp;
					do
					{
						temp = functionStack.top();
						functionStack.pop();
					} while (temp != 'g' && temp != 'm' && temp != 'f');
					if (temp == 'f')
					{
						unsigned int tempX = numberStack.top();
						numberStack.pop();
						res = f(tempX);
						
					}
					else if (temp == 'm')
					{
						unsigned int tempY = numberStack.top();
						numberStack.pop();
						unsigned int tempX= numberStack.top();
						numberStack.pop();
						res = m(tempX, tempY);
						
					}
					else 
					{
						unsigned int tempX = numberStack.top();
						numberStack.pop();
						res = g(tempX);
					}

					if (!functionStack.empty())
						numberStack.push(res);
					else
						cout << res << endl;

				}
				else if (c >= '0'&& c <= '9')
					equatNum += c;
				
			}
		}
	}
	
}
const char* filename = "myfile.txt";
int main()
{
	
	ifstream file("myfile.txt");
	if (!file.is_open())
	{
		cerr << "Couldn't open file!";

	}
	else
	{
		getResults(file);
	}
	file.close();
	system("pause");
	return 0;
}