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
	
	pos = malloc(REALL*sizeof(int));
	
	for(i=0; i<size; i++) {
		if(sandpile[i] >= 4) {
			numZcr++;
			if(numZcr%REALL == 0)
				pos = realloc(pos, numZcr+REALL);
			pos[k] = i;
		}
	}
	return 0;
}


void
avalanche(int* sandpile, int size)
{
	int i,start, numZcr;
	int *pos;
	
	numZcr = 0;
	for(i=0; numZcr==0; i++) {
		addgrain(sandpile, size);
		numZcr = checkZcr(sandpile, size, pos);
	}
	printf("we had to add %d grains before an avalanche\n",i);
	printf("We reached Zcr %d times\n", numZcr);
	free(pos);
}

int
main(int argc, char **argv) 
{
	int opt,L,L2,a;
	int *sandpile;
	char *check;
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
	init_ran(0);
	
	L2 = L*L;
	sandpile = calloc(L2, sizeof(int));
	
	avalanche(sandpile, L2);
	
	free(sandpile);
	return 0;
}
