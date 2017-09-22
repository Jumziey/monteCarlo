#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "../ising.h"
#include "../ran.h"
#include "queue.h"

static inline 
int 
abovef(int pos, int L) {
	if(pos < L) {
		return ((L*(L-1))+pos);
	}
	return (pos-L);
}
static inline
int
belowf(int pos, int L) {
	if((pos+L) >= (L*L)) {
		return pos%L;
	}
	return pos+L;
}
static inline
int
rightf(int pos, int L) {
	if( ((pos+1)%L) == 0 ) {
		return pos-(L-1);
	}
	return pos+1;
}
static inline
int
leftf(int pos, int L) {
	if( pos%L == 0 ) {
		return pos+(L-1);
	}
	return pos-1;
}


bool clusterAdd(int spin[], int neighbour , int startState, double prob){
	if(spin[neighbour] == startState && dran()<prob) {
		spin[neighbour] *= -1;
		return true;
	}
	return false;
}

int update(Par* par, int* spin) {

	int state,size,acc,pos;
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
	while(!queueIsEmpty(q)){ 
		pos = queuePop(q);
		if(clusterAdd(spin, abovef(pos,par->L), state, prob)) {
			queueAdd(q, abovef(pos,par->L));
			acc++;
		}
		if(clusterAdd(spin, belowf(pos,par->L), state, prob)) {
			queueAdd(q, belowf(pos,par->L));
			acc++;
		}
		if(clusterAdd(spin, rightf(pos,par->L), state, prob)) {
			queueAdd(q, rightf(pos,par->L));
			acc++;
		}
		if(clusterAdd(spin, leftf(pos,par->L), state, prob)) {
			queueAdd(q, leftf(pos,par->L));
			acc++;
		}
	}
	queueDestroy(q);
	return acc;
}

	
	
