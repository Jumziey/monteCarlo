/*
 * Implementation of lifo queue 
 * with integers
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void queueAdd(queue *q, int elem){
	q->arr[q->count] = elem;
	q->count++;
}
int queuePop(queue *q) {
	q->count--;
	return q->arr[q->count];
}

queue* queueCreate(int size) {
	queue *q = malloc(sizeof(queue)*1);
	q->arr = malloc(sizeof(int)*size);
	q->count = 0;
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


