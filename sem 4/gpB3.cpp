/*Construct an expression tree from the given prefix expression eg. +--a*bc/def and traverse it using post order traversal (non recursive) and then delete the entire tree.*/
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Represents a node of the required tree
struct node {
	char data;
	node *left, *right;
};

// Function to recursively build the expression tree
char* add(node** p, char* a)
{

	// If its the end of the expression
	if (*a == '\0')
		return '\0';

	while (1) {
		char* q = "null";
		if (*p == nullptr) {

			// Create a node with *a as the data and
			// both the children set to null
			node* nn = new node;
			nn->data = *a;
			nn->left = nullptr;
			nn->right = nullptr;
			*p = nn;
		}
		else {

			// If the character is an operand
			if (*a >= 'a' && *a <= 'z') {
				return a;
			}

			// Build the left sub-tree
			q = add(&(*p)->left, a + 1);

			// Build the right sub-tree
			q = add(&(*p)->right, q + 1);

			return q;
		}
	}
}

// Function to print the infix expression for the tree
void inr(node* p) // recursion
{
	if (p == nullptr) {
		return;
	}
	else {
		inr(p->left);
		cout << p->data << " ";
		inr(p->right);
	}
}

// Function to print the postfix expression for the tree
void postr(node* p)
{
	if (p == nullptr) {
		return;
	}
	else {
		postr(p->left);
		postr(p->right);
		cout << p->data << " ";
	}
}

int main()
{
	node* s = nullptr;
	char a[] = "*+ab-cd";
	add(&s, a);
	cout << "The Infix expression is:\n ";
	inr(s);
	cout << "\n";
	cout << "The Postfix expression is:\n ";
	postr(s);
	return 0;
}

