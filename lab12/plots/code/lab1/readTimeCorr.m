function timeEnergy = readTimeCorr(update, L, temps, ntherm, nblock, nsamp, seed)

	keys = {'L' 't' 'ntherm' 'nblock' 'nsamp' 'seed'};
	vals = [0 0 0 nblock nsamp seed];

	filename='';

	timeEnergy = [];
	
	if strcmpi('metro', update)
		cd ../../../Metro/data
	elseif strcmpi('cluster', update)
		cd ../../../Cluster/data
	else
		error('Wrong update function was choosen')
	end

	if ntherm == 0
		if strcmpi('metro', update)
				vals(3) = L.^2;
			else
				vals(3) = 1000;
			end
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
		filename = strcat(filename, 'tcorr');
		%Lets save away the heat capacities and magnisations
		tmp = load(filename)';
		timeEnergy = [timeEnergy tmp];
		filename = '';
	end
	cd ../../plots/code/lab1
end
