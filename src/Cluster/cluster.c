#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../ising.h"
#include "../ran.h"
#include "queue.h"


bool clusterAdd(int spin[], int neighbour , int startState, double prob){
	if(spin[neighbour] == startState && dran()<prob) {
		spin[neighbour] *= -1;
		return true;
	}
	return false;
}

int update(Par* par, int* spin) {

	int state, size,acc,pos;
	double prob;
	
	acc = 0;
	size = par->L*par->L;
	queue* q = queueCreate(size);
	
	//initialize
	pos = iran()%size;
	state = spin[pos];
	spin[pos] *= -1;
	queueAdd(q,pos);

	prob = 1.0-exp(-2.0/par->t);
	//Repeat as long the queue is non-empty
	for(;!queueIsEmpty(q);pos = queuePop(q)) {
		if(clusterAdd(spin, spin[ABOVE(pos,par->L)], state, prob)) {
			queueAdd(q, ABOVE(pos,par->L));
			acc++;
		}
		if(clusterAdd(spin, spin[BELOW(pos,par->L)], state, prob)) {
			queueAdd(q, BELOW(pos,par->L));
			acc++;
		}
		if(clusterAdd(spin, spin[RIGHT(pos,par->L)], state, prob)) {
			queueAdd(q, RIGHT(pos,par->L));
			acc++;
		}
		if(clusterAdd(spin, spin[LEFT(pos,par->L)], state, prob)) {
			queueAdd(q, LEFT(pos,par->L));
			acc++;
		}
	}
	queueDestroy(q);
	return acc;
}

	
	
