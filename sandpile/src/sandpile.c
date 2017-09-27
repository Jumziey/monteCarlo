/* What do we need
 *  PARAMETERS
 *   -L size
 *   -a - number of avalanches we want
 *  RESULT
 *   -Average avalanche size
 *	 -Average time of avalanche
 *
 * We add grains until we have an avalanche.
 * Then we measure avalanche size and average avalanche time. 
 * and we do this until we done it nsamp times.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>

#ifdef VIS
	#include "visualize.h"	
#endif


#include "ran.h"

void
error(char *err)
{
	fprintf(stderr, "%s", err);
	exit(1);
}

void
addgrain(int* sandpile, int size)
{
	sandpile[iran()%size]++;
}

int
checkZcr(int* sandpile, int size, int *pos)
{
	int i;
	int numZcr = 0, k = 0;
	
	for(i=0; i<size; i++) {
		if(sandpile[i] >= 4) {
			numZcr++;
			pos[k++] = i;
		}
	}
	return numZcr;
}

void
distribute(int* sandpile, int L, int* pos, int numZcr)
{
	int i;

	/* Here we treat the borders as sand
	 * Flowing outside the boundary and dissapearing.
	 */
	for(i=0; i<numZcr; i++) {
		sandpile[pos[i]] -= 4;
		//right
		if( !(pos[i]%L==(L-1)) )
			sandpile[pos[i]+1]++;
		//left
		if(pos[i]%L)
			sandpile[pos[i]-1]++;
		//above
		if(pos[i]>=L)
			sandpile[pos[i]-L]++;
		//below
		if(pos[i]<(L*(L-1)))
			sandpile[pos[i]+L]++;
	}
}


void
avalanche(int* sandpile, int L, int* S, int* t)
{
	int i,start, numZcr, L2;
	int *pos;
	
	L2 = L*L;
	pos = malloc(L2*sizeof(int));
	
	//Add grains until avalanche start
	numZcr = 0;
	for(i=0; numZcr==0; i++) {
		addgrain(sandpile, L2);
		numZcr = checkZcr(sandpile, L2, pos);
	}
	*S += numZcr;
	//There is a minescule chance for infinity
	//loop if addgrain is to well distributed.
	//Thus the large limit of 1000.
	for(i=0; numZcr != 0; i++) {
		distribute(sandpile, L, pos, numZcr);
		numZcr = checkZcr(sandpile, L2, pos);
		*S += numZcr;
	}

	*t += i;
	free(pos);
}

double
sumpile(int *sandpile, int L)
{
	int i;
	double sum = 0.0;
	
	for(i=0; i<L*L; i++)
		sum += sandpile[i];
	
	return sum;
}

int
main(int argc, char **argv) 
{
	int opt,L,L2,a,i,init;
	int *sandpile;
	int S=0,t=0;
	char *check;
	char *filename, lval[50], aval[50], ival[50];
	FILE* fp;
	
	L = 0; a = 0;
	filename = calloc(200, sizeof(char));
	
	while((opt=getopt(argc,argv,"L:a:")) != -1) {
		switch(opt) {
			case 'L':
				optarg++;//Removing equal sign
				L = strtol(optarg,&check,10);
				if(*check != '\0')
					error("only take integers as argument to L\n");
				break;
			case 'a':
				optarg++;//Removing equal sign
				a = strtol(optarg,&check,10);
				if(*check != '\0')
					error("only take integers as argument to a\n");
				break;
			case '?':
				error("unknown parameter given\n");
			default:
				fprintf(stderr, "we shouldnt be here\n");
		}
	}
	init_ran(0);

	
	sandpile = calloc(L*L,sizeof(int));
	
	//Trying to get critical density
	//To create less of a skew in data
	double max = L*L*4;
	double sum = 0.0;
	
	//we wanna reach above 52% occupation
	//According to testing...
	for(i=0; (sum/max) < 0.52; i++) {
		avalanche(sandpile, L, &S, &t);
		sum = sumpile(sandpile, L);
		if(i%10 == 0)
			printf("sum/max = %8f\n", sum/max);
	}
#ifdef VIS
		visInit();
		visualize(sandpile,L);
#endif
	printf("Runs before 52%% occupation: %d\n", i);

	
	S=0; t=0;
	
	sprintf(lval, "%d", L);
	sprintf(aval, "%d", a);
	sprintf(ival, "%d", init);
	strcat(filename, "./../data/");
	strcat(filename, "L");
	strcat(filename, lval);
	strcat(filename, "a");
	strcat(filename, aval);
	printf("filename: %s\n", filename);
	
	fp = fopen(filename, "w");
	fprintf(fp, "Size\tTime\n");
	
	sleep(2);
	for(i=0; i<a; i++) {
		avalanche(sandpile, L, &S, &t);
#ifdef VIS
		visualize(sandpile, L);
#endif
		fprintf(fp, "%d\t%d\n",S, t);
		S = 0; t = 0;
		if(i%100 == 0)
			printf("Run %d executed\n", i);
	}
#ifdef VIS
		visClose();
#endif
	fclose(fp);
	free(filename);
	return 0;
}
