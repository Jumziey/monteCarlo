//Tabsize: 2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

#include "ran.h"
#include "ising.h"
tc
char fname[FNAMESIZE];	
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

double measure(Par *par, double *v, int *spin)
{
	int i,j;
	double m = 0.0,e = 0.0;

	//Energy left and right
	for(i=0; i<(par->L*par->L-1); i=i+2) {
		e -= spin[i]*spin[LEFT(i,par->L)];
		e -= spin[i]*spin[RIGHT(i,par->L)];
	}
	//Energy Above And Below
	for(i=0; i<par->L-1; i=i+2) {
		for(j=0; j<par->L; j++) {
			e -= spin[i*par->L+j]*spin[ABOVE(i*par->L+j,par->L)];
			e -= spin[i*par->L+j]*spin[BELOW(i*par->L+j,par->L)];
		}
	}
	//Special case if par->L is odd
	if(par->L%2) {
		for(j=0; j<par->L; j++)
			e -= spin[par->L*par->L+j]*spin[ABOVE(par->L*par->L+j,par->L)];
	}
	
	//Magnetisation
	for(i=0; i<(par->L*par->L); i++)
		m += spin[i];
	
	//Values for the whole system
	v[0] += e;
	v[1] += fabs(m);
	v[2] += pow(e,2);
}

void result(Par *par, double* v, int divide, int final)
{
	double eSys, mSys, e2Sys;
	double cPerSpin, ePerSpin, mPerSpin, sysSize;

	sysSize = par->L*par->L;
	eSys = v[0]/divide;
	mSys = v[1]/divide;
	e2Sys = v[2]/divide;
	
	cPerSpin = 1/pow(par->t,2) * (( e2Sys - pow(eSys,2))) / sysSize;
	ePerSpin = eSys/sysSize;
	mPerSpin = mSys/sysSize;

  if (final)
    printf("  --------  --------  --------\n");
	printf(" %8f  %8f  %8f \n", ePerSpin, cPerSpin, mPerSpin);
}

/*Here we actually put j=boltzmann because of reasons that 
 * For reasons that even escapes our awesome instructor
 */
double spinEnergy(Par *par, int ind, int *spin) {
	double e;
	e = 0.0;
	
	e -= spin[ind]*spin[ABOVE(ind,par->L)];
	e -= spin[ind]*spin[BELOW(ind,par->L)];
	e -= spin[ind]*spin[RIGHT(ind,par->L)];
	e -= spin[ind]*spin[LEFT(ind,par->L)];
	
	return e;
}

#define MAXRUNS 10
#define PARVALS 6
void saveData(Par *par, double* v,int divide)
{
	int i;
	char sysVal[PARVALS][MAXRUNS];
	char *sysValNames[] = {"L","t","ntherm","nblock","nsamp","seed"};
	char *filename;
	FILE* fp;
	
	filename = calloc(22+MAXRUNS*PARVALS + 5,sizeof(char));
	
	sprintf(sysVal[0], "%d", par->L);
	sprintf(sysVal[1], "%g", par->t);
	sprintf(sysVal[2], "%d", par->ntherm);
	sprintf(sysVal[3], "%d", par->nblock);
	sprintf(sysVal[4], "%d", par->nsamp);
	sprintf(sysVal[5], "%d", par->seed);
	
	char strtmp[10+MAXRUNS];
	strcpy(filename,"data/");
	for(i=0; i<PARVALS; i++) {
		strcpy(strtmp,sysValNames[i]);
		strcat(strtmp,sysVal[i]);
		filename = strcat(filename,strtmp);
	}
	printf("Finalized data saved to: %s\n", filename);
	
	double eSys, mSys, e2Sys;
	double cPerSpin, ePerSpin, mPerSpin, sysSize;

	sysSize = par->L*par->L;
	eSys = v[0]/divide;
	mSys = v[1]/divide;
	e2Sys = v[2]/divide;
	
	cPerSpin = 1/pow(par->t,2) * (( e2Sys - pow(eSys,2))) / sysSize;
	ePerSpin = eSys/sysSize;
	mPerSpin = mSys/sysSize;
	
	
	fp = fopen(filename, "w");
	fprintf(fp,"%8f %8f %8f\n", ePerSpin, cPerSpin, mPerSpin);
	printf("================== SAVED DATA ================\n");
	printf("%8f %8f %8f\n", ePerSpin, cPerSpin, mPerSpin);
	fclose(fp);
	
}

void mc(Par *par, int *spin)
{
  int i, iblock, isamp, istep, ntherm = par->ntherm;
  double t = par->t, acc, accept = 0.0, L2 = par->L*par->L;
  double v[] = {0.0, 0.0, 0.0};


  //Read in the configuration for the present parameters if already present.
  if (read_config(par, spin, fname))
  	ntherm = 0;

  //Write out information about the run: size, temperature,...
#ifdef CLU
  printf("2D Ising model with the Wolff cluster algorithm.\n");
#else
  printf("2D Ising model with the Metropolis algorithm.\n");
#endif

  printf("\n====    %d x %d     T = %g    ====\n", par->L, par->L, par->t);
  printf("\nntherm  nblock   nsamp   seed\n");
  printf(" %5d  %5d   %5d   %d\n", ntherm, par->nblock, par->nsamp, par->seed);
  
  printf("\n energy      cv        magn     \n");

  //Thermalize the system 
  for (i = 0; i < ntherm; i++)
    update(par, spin);

  for (iblock = 0; iblock < par->nblock; iblock++) {
    for (isamp = 0; isamp < par->nsamp; isamp++) {
      accept += update(par, spin);
      measure(par, v, spin);
    }
    write_config(par, spin, fname);
    result(par,v,par->nsamp*(iblock+1),0);
  }
  
	result(par,v,par->nblock*par->nsamp,1);
  acc = accept * 100.0 / (L2 * (par->nblock) * (par->nsamp));
  printf("\nAcceptance: %5.2f\n", acc);

	saveData(par,v,par->nblock*par->nsamp);
}

int 
initialize_mc(Par *par, int *spin) {
  int i,j, L2 = par->L * par->L;
  char *f2;

  if (!par->L) {
    printf("Give system size N!\n");
    return 0;
  }

  init_ran(par->seed);

  init_tables(par);

  sprintf(fname, "%3.3d_%5.3f", par->L, par->t);

  mc(par, spin);

  return 1;
}

int read_args(Par *par, char *arg)
{
  int st;
  static int *spin = NULL;
  char *s;

  if (!strcmp(arg, "run")) {
    if(initialize_mc(par, spin)) {
    	/* We free spin only to get 
    	 * a better result from valgrind ;)
    	 */
    	free(spin);
    	return 1;
    } else {
    	return 0;
    }
	}
  s = strchr(arg, '=');

  if (!s) {
    fprintf(stderr, "Command '%s' not recognized, expected format: '<name>=<value>'.", arg);
    return 0;
  }

  *s++ = '\0';

  if (!strcmp(arg, "L")) {
    int i, L2;
    par->L = strtod(s, NULL);
    L2 = par->L * par->L;
    spin = realloc(spin, L2 * sizeof(int));
    for (i = 0; i < L2; i++)
      spin[i] = 1;
#ifdef CLU
    par->ntherm = 1000;
#else
    par->ntherm = L2;
#endif

    return 1;
  }

  if (!strcmp(arg, "T")) {
    par->t = strtod(s, NULL);
    return 1;
  }

  if (!strcmp(arg, "ntherm")) {
    par->ntherm = strtol(s, NULL, 0);
    return 1;
  }

  if (!strcmp(arg, "nblock")) {
    par->nblock = strtol(s, NULL, 0);
    return 1;
  }

  if (!strcmp(arg, "nsamp")) {
    par->nsamp = strtol(s, NULL, 0);
    return 1;
  }

  if (!strcmp(arg, "seed")) {
    par->seed = strtol(s, NULL, 0);
    return 1;
  }

  if (!strcmp(arg, "read")) {
    return read_config(par, spin, s);
  }

  fprintf(stderr, "No such variable name: '%s'.\n", arg);
  return 0;
}

int
main(int argc, char *argv[])
{
  int i, iarg;
  Par *par = malloc(sizeof(Par));

  par->L = 0;
  par->t = 2.26;
  par->nblock = 1;
  par->nsamp = 10000;
  par->seed = 0;

  if (argc == 1) {
    printf("Usage: %s L=16 T=2.26\n", argv[0]);
    printf("Optional arguments (with defaults) nblock=%d nsamp=%d ntherm=%d seed=%d\n",
	   par->nblock, par->nsamp, par->ntherm, par->seed);
    exit(EXIT_SUCCESS);
  }

  // Interpret the commands given in the argument list.
  for (iarg = 1; iarg < argc; iarg++)
    if (!read_args(par, argv[iarg]))
      exit(EXIT_FAILURE);

  free(par);
}
