#include <stdio.h>
#include <stdlib.h>

#include "../ising.h"
#include "../save.h"

#define NR_OF_FNAMES 3
int main() {
	int i, nrOfFnames;
	char** fname;
	char filename[] = "testfilename";

	Par par = {16, 2.2, 100, 100, 100, 0, filename};
	

	fname = dataFilenames(&par);
	for(i=0; i<NR_OF_FNAMES; i++) {
		printf("filename: %s\n", fname[i]);
	}

	return 0;
}
