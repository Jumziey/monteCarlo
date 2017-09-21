/*
 * Implementation of fifo queue 
 * with integers
 */

typedef struct queue{
	int* arr;
	int rear;
	int front;
	int count;
	int size;
} queue;

void queueAdd(queue*, int);
int queuePop(queue*);
queue* queueCreate(int);
void queueDestroy(queue*);
bool queueIsEmpty(queue*);

