#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;
const string filename = "expressionFile.txt";

struct variable
{
	char c;
	int var;

};
vector<variable> variables;
struct Node
{
	string data;
	Node *left, *right;
	Node(string _data = ""):data(_data),left(nullptr),right(nullptr){}
};

int getNumFromVar(char c)
{
	int len = variables.size();
	bool found = false;
	int var;
	for (int i = 0; i < len; i++)
	{
		if (variables[i].c == c)
		{
			found = true;
			var = variables[i].var;
		}
	}
	if (!found)
	{
		cout << "Enter a value for " << c << " : ";
		cin >> var;
		variable temp;
		temp.c = c;
		temp.var = var;
		variables.push_back(temp);
	}
		return var;
}
bool isNumber(char c)
{
	return  (c - '0' >= 0 && c - '0' <= 9);
	
}
bool isVar(char c)
{
	return (c >= 'a'&& c <= 'b');
}
bool isOperation(char c)
{
	return (c == '/' || c == '*' || c == '+' || c == '-');
}
void buildTreePrefix(Node*& tn,string str,int &pos)
{
	int strLen = str.size();
	if (pos == strLen)
		return;
	if(!tn)
		tn = new Node;
	if (str[pos] == ' ')
		pos++;
	if ( isNumber(str[pos])||isVar(str[pos]))
	{
		//create and add number
		string helper = "";
		while (str[pos] != ' '&&str[pos] != '\0')
		{
			helper += str[pos];
			++pos;
		}
		tn->data = helper;
	}
	else if(isOperation(str[pos]))
	{
		tn->data = str[pos];
		buildTreePrefix(tn->left,str, ++pos);
		buildTreePrefix(tn->right,str, ++pos);
	}
	
	
}
void printSufix(Node* t)
{

	if (!t)
	{
		return;
	}

	printSufix(t->left);
	printSufix(t->right);
	cout << t->data << ' ';

}
void printInfix(Node* root)
{
	if (!root)
	{
		return;
	}
	if (!(root->left == nullptr && root->right == nullptr))
		cout << "( ";
	printInfix(root->left);
	cout << root->data << ' ';
	printInfix(root->right);
	if (!(root->left == nullptr && root->right == nullptr))
		cout << ") ";
	
}
int toInt(string str)
{
	return stoi(str);
}

int solve(Node* root)
{
	if (!root)
		return 0;
	if (root->data == "+")
	{
		return solve(root->left) + solve(root->right);
	}
	else if (root->data == "-")
	{
		return solve(root->left) - solve(root->right);
	}
	else if (root->data == "/")
	{
		return solve(root->left) / solve(root->right);
	}
	else if(root->data == "*")
	{
		return solve(root->left) * solve(root->right);
	}
	else if (isVar(root->data[0]))
	{
		return getNumFromVar(root->data[0]);
	}
	else return toInt(root->data);
}
void readFromFile(vector<string> & expressions)
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
		cerr << "Couldn't open file" << endl;
	string buffer;
	while (!file.eof())
	{
		getline(file, buffer);
		expressions.push_back(buffer);
	}
}

int main()
{
	vector<string> expressions;
	readFromFile(expressions);
	
	int numExp = expressions.size();
	for (int i = 0; i < numExp; i++)
	{
		Node* root = nullptr;
		int startPos = 0;
		buildTreePrefix(root, expressions[i], startPos);
		if (root)
		{
			printInfix(root);
			cout << endl;
			printSufix(root);
			cout << endl;
			cout << "Result: " << solve(root) << endl;
		}
	}
	system("pause");
	return 0;
}