#include <math.h>
#include "ising.h"
#include "ran.h"

int update(Par* par, int* spin) {
	int state, size,i,j;
	
	size = par->L*par->L;
	//I'll be suprised if the queue gets bigger
	queueInit(size) 
	
	pos = ceil(size/dran());
	state = spin[pos];
	spin[pos] *= -1;
	queuePut(pos);
	
	prob = 1-exp(-2/par->t);
	while((i = queueGet())!= 0) {
		if(spin[ABOVE(i,par->L)] == state)
			if(dran()<=prob) {
				spin[ABOVE(i,par->L)] *= -1;
				queuePut(ABOVE(i,par->L));
			}
		if(spin[BELOW(i,par->L)] == state)
			if(dran()<=prob) {
				spin[BELOW(i,par->L)] *= -1;
				queuePut(BELOW(i,par->L));
			}
		if(spin[RIGHT(i,par->L)] == state)
			if(dran()<=prob) {
				spin[RIGHT(i,par->L)] *= -1;
				queuePut(RIGHT(i,par->L));
			}
		if(spin[LEFT(i,par->L)] == state)
			if(dran()<=prob) {
				spin[LEFT(i,par->L)] *= -1;
				queuePut(LEFT(i,par->L));
			}
	}
	queueFree();
	return 0; // NO ACCEPTENCE FOR NOW! 
}

	
	
	
