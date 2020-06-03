#include <bits/stdc++.h> 
#include <cstdio>
#include <cstdlib>
#include <cstddef>

#if 0
#define MAX_QUEUE_SIZE 100
typedef struct queue_ {
	int arr[MAX_QUEUE_SIZE];
	int size = MAX_QUEUE_SIZE;
	int front, rear;
} queue;

void quueInit(queue *q) {
	q->front=0;
	q->rear=0;
}

bool enQueue(queue *q, int val) {
	if ((q->rear + MAX_QUEUE_SIZE - q->front) == MAX_QUEUE_SIZE-1)
		return false;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->arr[q->rear] = val;
	return true;
}

bool deQueue( queue *q, int *val) {
	if (q->rear == q->front)
		return false;
	*val = q->arr[q->front];
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return true;
}

#else
typedef struct node_ {
	int val;
	struct node_ *next;	
}node;


typedef struct queue_ {
	node *front, *rear;
} queue;

bool enQueue( int val, queue *q) {
	node *n=(node *) malloc(sizeof(node));
	if (!n)
		return false;
	n->val = val;
	if (q->rear == NULL) {
		q->front = q->rear = n;
	} else {
		node *t = q->rear->next;
		q->rear->next = n;
		n->next = t;
		q->rear = n;
	}
	return true;
}

bool deQueue( int *val, queue *q) {
	if (q->front == NULL) {
		return false;
	} 
	if (q->front == q->rear) {
		*val = q->front->val;
		free(q->front);
		q->front = q->rear = NULL; 
	} else {
		*val = q->front->val;
		node *t = q->front;
		q->front= q->front->next;
		t->next = NULL;
		free(t);
	}
	return true;
}

#endif

int main(){
	return 0;
}