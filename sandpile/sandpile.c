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

#define REALL 5
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


/* Here we treat the borders as sand
 * Flowing outside the boundary.
 */
void
distribute(int* sandpile, int size, int* pos, int numZcr)
{
	int i;
	int L;
	
	L = (int)sqrt(size);
	
	for(i=0; i<numZcr; i++) {
		sandpile[pos[i]] -= 4;
		//right
		if(!(pos[i]%L==(L-1)))
			sandpile[pos[i]+1]++;
		//left
		if(pos[i]%L)
			sandpile[pos[i]-1]++;
		//above
		if(pos[i]>=L)
			sandpile[pos[i]-L]++;
		//below
		if(pos[i]<L*(L-1))
			sandpile[pos[i]+L]++;
	}
}


void
avalanche(int size, double* S, double* t)
{
	int i,start, numZcr;
	int *pos, *sandpile;
	
	sandpile = calloc(size,sizeof(int));
	pos = malloc(size*sizeof(int));
	
	//Add grains until avalanche start
	numZcr = 0;
	for(i=0; numZcr==0; i++) {
		addgrain(sandpile, size);
		numZcr = checkZcr(sandpile, size, pos);
	}
	*S += numZcr;
	
	for(i=0; numZcr != 0; i++) {
		distribute(sandpile, size, pos, numZcr);
		numZcr = checkZcr(sandpile, size, pos);
		*S += numZcr;
	}
	
	*t += i;
	free(pos);
	free(sandpile);
}

int
main(int argc, char **argv) 
{
	int opt,L,L2,a,i;
	char *check;
	char filename[150], lval[50], aval[50];
	FILE* fp;
	
	L = 0; a = 0;
	
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

	L2 = L*L;
	
	sprintf(lval, "%d", L);
	sprintf(aval, "%d", a);
	strcat(filename, "data/");
	strcat(filename, "L");
	strcat(filename, lval);
	strcat(filename, "a");
	strcat(filename, aval);
	printf("filename: %s\n", filename);
	
	fp = fopen(filename, "w");
	
	double S=0.0,t=0.0;
	int pS, pt;
	init_ran(0);
	for(i=0; i<a; i++) {
		pS = S; pt = t;
		avalanche(L2, &S, &t);
		fprintf(fp, "%f %f\n",S, t);
		S = 0; t = 0;
	}
	fclose(fp);
	return 0;
}
