function allRuns = readData(update, sizes, temps, ntherm, nblock, nsamp, seed)

	keys = {'L' 't' 'ntherm' 'nblock' 'nsamp' 'seed'};
	vals = [0 0 0 nblock nsamp seed];

	filename='';

	eSim = [];
	cSim = [];
	mSim = [];
	allRuns = [];
	
	if strcmpi('metro', update)
		cd ../../Metro/data
	elseif strcmpi('cluster', update)
		cd ../../Cluster/data
	else
		error('Wrong update function was choosen')
	end

	for L=sizes
		if ntherm == 0
			vals(3) = L.^2;
		else 
			vals(3) = ntherm;
		end
		vals(1) = L;
		for t=temps
			vals(2) = t;
			for i=1:6
				strtmp = strcat(char(keys(i)),num2str(vals(i)));
				filename = strcat(filename,strtmp);
			end
			%Lets save away the heat capacities and magnisations
			tmp = load(filename);
			eSim = [eSim tmp(1)];
			cSim = [cSim tmp(2)];
			mSim = [mSim tmp(3)];
			filename = '';
		end
		allRuns = [allRuns eSim' cSim' mSim'];
		eSim = [];
		cSim = [];
		mSim = [];
	end
	cd ../../plots/code
end
