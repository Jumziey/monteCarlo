/*
 * Implementation of lifo queue 
 * with integers
 */

typedef struct queue{
	int* arr;
	int count;
} queue;

void queueAdd(queue*, int);
int queuePop(queue*);
queue* queueCreate(int);
void queueDestroy(queue*);
bool queueIsEmpty(queue*);

