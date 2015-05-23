#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "ising.h"
#include "ran.h"

int update(Par* par, int* spin) {

	int state, size,acc,pos;
	int *in, *out, *mem;
	double prob;
	
	acc = 0;
	size = par->L*par->L;
	//I'll be suprised if the queue gets bigger
	queueInit(size);
	
	prob = 1.0-exp(-2.0/par->t);
	
	pos = uran()%size;
	state = spin[pos];
	spin[pos] *= -1;
	in = out = mem  = calloc(sizeof(int),size);
	
	*in++ = pos;
	while(in-out) {
		pos = *out++;
		if(spin[ABOVE(pos,par->L)] == state && dran()<prob) {
			spin[ABOVE(pos,par->L)] *= -1;
			*in++ = ABOVE(pos,par->L);
			acc++;
		}
		if(spin[BELOW(pos,par->L)] == state && dran()<prob) {
			spin[BELOW(pos,par->L)] *= -1;
			*in++ = BELOW(pos,par->L);
			acc++;
		}
		if(spin[RIGHT(pos,par->L)] == state && dran()<prob) {
			spin[RIGHT(pos,par->L)] *= -1;
			*in++ = RIGHT(pos,par->L);
			acc++;
		}
		if(spin[LEFT(pos,par->L)] == state && dran()<prob) {
			spin[LEFT(pos,par->L)] *= -1;
			*in++ = LEFT(pos,par->L);
			acc++;
		}
	}
	free(mem);
	return acc;
}

	
	
	
