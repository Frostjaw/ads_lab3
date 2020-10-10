// lab 3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

#define ROWS 10
#define MAX_KEY 100
char Win[ROWS][81];


class Node 
{
	int value;
	Node *left, *right;
	Node(int val) { value = val; left = right = NULL; }
	friend class Tree;
};

class Tree
{
	Node *root, *current, *parent;
	void Print(Node *curr, int line, int lcol, int rcol);
public:
	// 1 variant:
	/*Tree() { root = current = parent = NULL; }
	Tree(int val) { root = new Node(val); current = parent = NULL; }*/
	// 2 variant:
	Tree() { root = new Node(MAX_KEY); current = parent = NULL; }
	void Add(int val);
	void Print();
	Node* search(int val);
	void remove(int val);
};

//Add s 1 variantom
/*void Tree::Add(int val)
{
	Node *newNode = new Node(val);
	current = root; parent = NULL;
	while (current)
	{
		parent = current;
		if (current->value < val) current = current->right;
		else current = current->left;
	}
	if (!root) root = newNode;
	else if (parent->value < val) parent->right = newNode;
	else parent->left = newNode;
}*/

//Add s 2 variantom
void Tree::Add(int val)
{
	Node *newnode = new Node(val);
	parent = root; current = root->left;
	while (current != NULL)
	{
		parent = current;
		if (val > current->value) current = current->right;
		else current = current->left;
	}
	if (val > parent->value) parent->right = newnode;
	else parent->left = newnode;
}

Node* Tree::search(int val)
{
	parent = root; current = root->left;
	while (current != NULL && current->value != val)
	{
		parent = current;
		if (val > current->value) current = current->right;
		else current = current->left;
	}
	return current;	// NULL, если вершина не найдена
}

void Tree::remove(int val)
{
	if (!search(val)) return;
	// удаляется  лист
	if (!current->left && !current->right)
	{
		if (current == parent->left)
			parent->left = NULL;
		else parent->right = NULL;
	}
	// только  правое  поддерево
	else if (!current->left)
	{
		if (current == parent->left)
			parent->left = current->right;
		else parent->right = current->right;
	}
	// только  левое  поддерево
	else if (!current->right)
	{
		if (current == parent->left)
			parent->left = current->left;
		else parent->right = current->left;
	}
	// 2  поддерева
	else
	{
		Node *found = current;
		parent = current; current = current->left;
		while (current->right != NULL)
		{
			parent = current; current = current->right;
		}
		if (current == parent->left)		// вариант 1
			parent->left = current->left;
		else parent->right = current->left; // вариант 2
		found->value = current->value;
	}
	delete(current);
}

void Tree::Print()
{
	int i;
	system("cls");

	for (i = 0; i < ROWS; i++)
		sprintf(Win[i], "%80s", " ");

	Print(root->left, 0, 0, 79);

	for (i = 0; i < ROWS; i++)
		printf("%s\n", Win[i]);
}

void Tree::Print(Node *curr, int line, int lcol, int rcol)
{
	char num[4];
	int cent = (lcol + rcol) / 2;
	if (!curr) return;

	sprintf(num, "%2d", curr->value);
	memcpy(Win[line] + cent, num, 2);

	Print(curr->left, line + 1, lcol, cent);
	Print(curr->right, line + 1, cent + 1, rcol);
}


int main()
{
	srand(time(0));
	//proverka vivoda s 1 variantom
	/*int i;
	Tree test(50);
	for (i = 0; i < 10; i++)
		test.Add(rand() % 100);
	test.Print();*/

	//proverka vivoda s 2 variantom
	/*int i;
	Tree test;
	for (i = 0; i < 10; i++)
	test.Add(rand() % 100);
	test.Print();*/

	//proverka poiska
	/*Tree test; int k;
	test.Add(29); test.Add(28); test.Add(19); test.Add(37); test.Add(12); test.Add(21); test.Add(40); test.Add(42); test.Add(39);
	test.Print();
	cout << "vvedite element dlya poiska: "; cin >> k;
	if (test.search(k) == NULL) cout << "element ne naiden" << endl;
	else cout << "element naiden" << endl;*/

	//proverka udaleniya lepestok = 12; levoe podderevo = 28; pravoe podderevo = 37; 2 poddereva = 29
	/*Tree test; int k;
	test.Add(29); test.Add(28); test.Add(19); test.Add(37); test.Add(12); test.Add(21); test.Add(40); test.Add(42); test.Add(39);
	test.Print();
	cout << "vvedite element dlya udaleniya: "; cin >> k;
	test.remove(k);
	test.Print();*/

	Tree test; int i, n, val, searchval, delval;
	cout << "vvedite kol-vo elementov: " << endl; cin >> n;
	for (i = 0; i < n; i++) test.Add(rand() % 100);
	test.Print();
	cout << "vvedite element dlya dobavleniya: " << endl; cin >> val;
	test.Add(val);
	test.Print();
	cout << "vvedite element dlya poiska: " << endl; cin >> searchval;
	if (test.search(searchval) == NULL) cout << "element ne naiden" << endl;
	else cout << "element naiden" << endl;
	system("pause");
	test.Print();
	cout << "vvedite element dlya udaleniya: " << endl; cin >> delval;
	test.remove(delval);
	test.Print();	
    return 0;
}

