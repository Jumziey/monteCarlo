#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

#include "ising.h"

#define MAXRUNS 10
#define PARVALS 6
#define NR_OF_FNAMES 3
/*
 * Returns an array of strings as
 * a[0] = filename
 * a[1] = filnametcorr
 * a[2] = filenamebinders
 */
char** dataFilenames(Par* par) {
	int i;
	char* filename;
	char* filenameTcorr;
	char* filenameBinders;
	char sysVal[PARVALS][MAXRUNS];
	char *sysValNames[] = {"L","t","ntherm","nblock","nsamp","seed"};

	filename = calloc(22+MAXRUNS*PARVALS + 7 + 1 + strlen(par->datadir) ,sizeof(char));
	filenameTcorr = calloc(22+MAXRUNS*PARVALS + 7 + 1 + strlen(par->datadir) ,sizeof(char));
	filenameBinders = calloc(22+MAXRUNS*PARVALS + 7 + 1 + strlen(par->datadir) ,sizeof(char));

	sprintf(sysVal[0], "%d", par->L);
	sprintf(sysVal[1], "%g", par->t);
	sprintf(sysVal[2], "%d", par->ntherm);
	sprintf(sysVal[3], "%d", par->nblock);
	sprintf(sysVal[4], "%d", par->nsamp);
	sprintf(sysVal[5], "%d", par->seed);
	
	strcpy(filename, par->datadir);
	strcat(filename, "/");

	for(i=0; i<PARVALS; i++) {
		strcat(filename,sysValNames[i]);
		strcat(filename,sysVal[i]);
	}
	strcpy(filenameTcorr, filename);
	strcat(filenameTcorr, "tcorr");

	strcpy(filenameBinders, filename);
	strcat(filenameBinders, "binders");


	char** fnames = calloc(3, sizeof(filename));
	fnames[0] = filename;
	fnames[1] = filenameTcorr;
	fnames[2] = filenameBinders;
	return fnames;

}

void freeDataFilenames(char** fnames) {
	int i, nrOfFnames;
	nrOfFnames = sizeof(fnames)/sizeof(fnames[0]);
	for(i=0; i<nrOfFnames; i++) {
		free(fnames[i]);
	}
	free(fnames);
}

void saveData(Par *par, double* v, double* tcorr, double* mag, int saveTcorr, int saveBinders)
{
	int i, isamp;
	char** fnames;
	FILE* fp;

	int L2;
	double eSys, mSys, e2Sys;
	double ePerSpin, mPerSpin, cPerSpin;


	fnames = dataFilenames(par);
	printf("Finalized data saved to: %s\n", fnames[0]);
		
	L2 = par->L*par->L;
	
	eSys = v[0];
	mSys = v[1];
	e2Sys = v[2];
	
	ePerSpin = eSys/L2;
	cPerSpin = 1/pow(par->t,2) * (e2Sys - pow(eSys,2))/L2;
	mPerSpin = mSys/L2;
	
	fp = fopen(fnames[0], "w");
	fprintf(fp,"%8f %8f %8f\n", ePerSpin, cPerSpin, mPerSpin);
	fclose(fp);	
	printf("data saved to: %s\n", fnames[0]);
	
	//Save timecorrelation
	if(saveTcorr) {
		fp = fopen(fnames[1], "w");
		for(isamp = 0; isamp < par->nsamp; isamp++)
			fprintf(fp, "%16f ", tcorr[isamp]);
		fprintf(fp,"\n");
		fclose(fp);
		printf("Timecorr data saved to: %s\n", fnames[1]);
	}
	
	//Binder's cumulant
	if(saveBinders) {
		fp = fopen(fnames[2], "w");
		printf("magblock test: %8f    %8f\n",mag[0]/pow(L2,2),mag[1]/pow(L2,4));
		fprintf(fp, "%8f %8f \n", mag[0]/pow(L2,2), mag[1]/pow(L2,4));
		fclose(fp);
		printf("Binders data saved to: %s\n", fnames[2]);
	}
	
	freeDataFilenames(fnames);
}

/*Returns 1 if data allready exists
 * 0 if not
 */
int dataExists(Par *par, int checkTcorr, int checkBinders)
{
	int i, isamp, nrOfFnames;
	char sysVal[PARVALS][MAXRUNS];
	char *sysValNames[] = {"L","t","ntherm","nblock","nsamp","seed"};
	char **fnames;
	FILE* fp;
	
	fnames = dataFilenames(par);
	
	//main file
	if(access(fnames[0],F_OK) != 0) {
		printf("FILE DOES NOT EXIST, %s\n", fnames[0]);
		return 0; //File does not exists
	}
	printf("FILE EXISTS: %s\n", fnames[0]);
	
	//tcorr file
	if(checkTcorr) {
		if(access(fnames[1],F_OK) != 0) {
			printf("FILE DOES NOT EXIST, %s\n", fnames[1]);
			return 0; //File does not exists
		}
		printf("FILE EXISTS: %s\n", fnames[1]);
	}

	//binders file
	if(checkBinders) {
		if(access(fnames[2],F_OK) != 0) {
			printf("FILE DOES NOT EXIST, %s\n", fnames[2]);
			return 0; //File does not exists
		}
		printf("FILE EXISTS: %s\n", fnames[2]);
	}

	freeDataFilenames(fnames);
	return 1;
}
