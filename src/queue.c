/* An naive implementation 
 * fo an fifo queue
 * It can only be runned one instance at a time
 * and specifically for storing spins
 * but this is enough for this program.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>


int maxSize, curSize, in, out;
int *queue;

int
queueInit(int reqSize) {
	maxSize = reqSize;
	curSize = in = out = 0;
	queue = malloc(reqSize*sizeof(int));
	if(queue == NULL)
		return -1;
	return 0;
}

void
queuePut(int val) {
	if(curSize == maxSize) {
		fprintf(stderr, "The queue got maxed out\n");
		exit(20);
	}
	queue[in] = val;
	curSize++;
	in++;
	if(in == maxSize)
		in = 0;
}

int
queueGet() {
	int ret;
	
	if(curSize == 0) {
		return 0; //You cant have zero spin
	}
	ret = queue[out];
	curSize--;	
	out++;
	
	if(out == maxSize)
		out = 0;
	return ret;
}

void
queueFree() {
	free(queue);
}
