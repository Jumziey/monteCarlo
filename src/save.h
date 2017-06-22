void saveData(Par *par, double* v, double* tcorr, double* mag, int saveTcorr, int saveBinders);
int dataExists(Par *par, int checkTcorr, int checkBinders);
char** dataFilenames(Par* par);
