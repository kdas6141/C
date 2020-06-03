#include <bits/stdc++.h> 
#include <cstdio>
#include <cstdlib>
#include <cstddef>

typedef struct node_ { 
	int val;
	struct node_ * next;
} node;

node *top;

void push(int val) {
	node *t=(node *) malloc(sizeof(node));
	if (!t) {
		printf("\nHeap overflow.");
		exit(1);
	}
	t->val = val;
	t->next = top;
	top = t;
} 

bool empty() {
	return top == NULL;
}

int peek() {
	if (empty())
		return INT_MIN;
	return top->val;
}

void pop() {
	node *t;
	if (!top) {
		printf ("\n stack underflow");
	} else {
		t = top;
		top = top->next;
		t->next = NULL;
		free (t);
	}
}

int main(){
	return 0;
}