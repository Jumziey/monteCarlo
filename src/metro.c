#include <math.h>
#include <stdio.h>
#include "ising.h"
#include "ran.h"


double eDiffValues[5];

void init_tables(Par *par)
{
	eDiffValues[0] = 1;
	eDiffValues[1] = exp(-4/par->t);
	eDiffValues[2] = exp(-8/par->t);
	eDiffValues[3] = exp(4/par->t);
	eDiffValues[4] = exp(8/par->t);
}


double energyDiff(int eDiff) {
	switch(eDiff) {
		case 0:
			return eDiffValues[0];
			break;
		case 4:
			return eDiffValues[1];
			break;
		case 8:
			return eDiffValues[2];
			break;
		case -4:
			return eDiffValues[3];
			break;
		case -8:
			return eDiffValues[4];
			break;
		default:
			fprintf(stderr,"Something wrong with the eDiff\n");
			exit(2);
	}
}


int update(Par *par, int *spin)
{
	int i,j,ind, eDiff;
	double curEnergy, newEnergy,prob,b;
	int accept=0;
	
	for(i=0; i<par->L; i++) {
		for(j=0; j<par->L; j++) {
			ind = i*par->L + j;
		
			curEnergy = spinEnergy(par,ind,spin);

			spin[ind] = spin[ind]*(-1);
			newEnergy = spinEnergy(par,ind,spin);

			eDiff = newEnergy-curEnergy;
			
			prob = fmin(1.0, energyDiff(eDiff));
			double test = dran();
			if(test > prob) 
				spin[ind] = spin[ind]*(-1);
			 else 
				accept++;
			
		}
	}
  return accept;
}
