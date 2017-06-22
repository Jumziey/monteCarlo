

void timecorr(int nsamp, double* vserie, double* tcorr) {
	int isamp;
	double vavg = 0.0;
	
	for(isamp = 0; isamp < nsamp; isamp++)
		vavg += vserie[isamp];
	vavg /= nsamp;
	
	for(isamp = 0; isamp < nsamp; isamp++) 
		vavg += vserie[isamp];
	vavg /= nsamp;
	
	for(isamp = 0; isamp < nsamp; isamp++)
		tcorr[isamp] += (vserie[0]-vavg)*(vserie[isamp]-vavg);
}

void tcorrnorm(int nsamp, double* tcorr) {
	int isamp;
	double max=0.0, min=0.0;
	
	for(isamp = 0; isamp < nsamp; isamp++)
		if(tcorr[isamp] < min)
			min = tcorr[isamp];
	
	for(isamp = 0; isamp < nsamp; isamp++) {
		if(min < 0)
			tcorr[isamp] -= min; //Yes logic is slightly obfuscated
		if(tcorr[isamp] > max)
			max = tcorr[isamp];
	}
	
	for(isamp = 0; isamp < nsamp; isamp++)
		tcorr[isamp] /= max;
}
