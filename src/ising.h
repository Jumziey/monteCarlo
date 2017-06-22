
#define FNAMESIZE 64


typedef struct Par {
  int L;
  double t;
  int ntherm, nblock, nsamp, seed;
	char* datadir;
} Par;

// In config.c
extern int write_config(Par *par, int *spin, char *fname);
extern int read_config(Par *par, int *spin, char *fname);

// An update function that can be implemented
// depending on what scheme one wants
int update(Par*, int*);

// In ising.c
void init_tables(Par* par);
double energyDiff(int eDiff);
double spinEnergy(Par *par, int ind, int *spin);

//Defined for the spin matrix, using periodic boundaries
#define ABOVE(ind,L) ((ind-(L-1)) <= 0) 			? (L*L-1+(ind-(L-1))) : (ind-L)
#define BELOW(ind,L) ((ind+(L-1)) >= (L*L-1)) ? ((ind+(L-1))-(L*L-1)) : (ind+L)
#define RIGHT(ind,L) (ind == L*L-1) 					? 0 : (ind+1)
#define LEFT(ind,L)  (ind == 0) 							? (L*L-1) :  (ind-1)
