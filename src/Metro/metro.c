#include <math.h>
#include "../ising.h"
#include "../ran.h"

/* An update function written especially for the
 * metro update scheme
 */
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
