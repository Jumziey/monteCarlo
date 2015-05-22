#include <math.h>
#include <stdio.h>

#include "queue.h"
#include "ising.h"
#include "ran.h"

int update(Par* par, int* spin) {

	int state, size,acc,pos;
	double prob;
	
	acc = 0;
	size = par->L*par->L;
	//I'll be suprised if the queue gets bigger
	queueInit(size);
	
	pos = uran()%size;
	state = spin[pos];
	spin[pos] *= -1;
	queuePut(pos);
	
	prob = 1.0-exp(-2/par->t);
	while((pos = queueGet())!= 0) {
		if(spin[ABOVE(pos,par->L)] == state && dran()<prob) {
			spin[ABOVE(pos,par->L)] *= -1;
			queuePut(ABOVE(pos,par->L));
			acc++;
		}
		if(spin[BELOW(pos,par->L)] == state && dran()<prob) {
			spin[BELOW(pos,par->L)] *= -1;
			queuePut(BELOW(pos,par->L));
			acc++;
		}
		if(spin[RIGHT(pos,par->L)] == state && dran()<prob) {
			spin[RIGHT(pos,par->L)] *= -1;
			queuePut(RIGHT(pos,par->L));
			acc++;
		}
		if(spin[LEFT(pos,par->L)] == state && dran()<prob) {
			spin[LEFT(pos,par->L)] *= -1;
			queuePut(LEFT(pos,par->L));
			acc++;
		}
	}
	queueFree();
	return acc;
}

	
	
	
