/*
 * Implementation of fifo queue 
 * with integers
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void queueAdd(queue *q, int elem){
	if(q->count >= q->size) {
		 printf("queue overflow\n");
		 exit(1);
	}
	q->count++;

	q->arr[q->rear] = elem;
	if(q->rear == (q->size-1))
		q->rear = 0;
	else 
		q->rear++;
}

int queuePop(queue *q) {
	if(q->count <= 0) {
		printf("queue underflow\n");
		exit(1);
	}
	q->count--;

	if(q->front == (q->size-1)) {
		q->front = 0;
		return q->arr[q->size-1];
	}
	return q->arr[q->front++];
}

queue* queueCreate(int size) {
	queue *q = malloc(sizeof(queue)*1);
	q->arr = malloc(sizeof(int)*size);
	q->front = q->rear = q->count = 0;
	q->size = size;
	return q;
}

void queueDestroy(queue *q){
	free(q->arr);
	free(q);
}

bool queueIsEmpty(queue* q) {
	if(q->count == 0) 
		return true;
	return false;
}


