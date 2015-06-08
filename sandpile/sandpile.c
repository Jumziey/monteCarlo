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

void
error(char *err)
{
	fprintf(stderr, "%s", err);
	exit(1);
}

int
main(int argc, char **argv) 
{
	int opt,L,a;
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
	
	printf("L: %d, a: %d\n", L, a);
	return 0;
}
