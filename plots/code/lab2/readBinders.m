function mag = readData(update, sizes, temps, ntherm, nblock, nsamp, seed)

	keys = {'L' 't' 'ntherm' 'nblock' 'nsamp' 'seed'};
	vals = [0 0 0 nblock nsamp seed];

	filename='';

	m2 = [];
	m4 = [];
	mag = [];
	
	if strcmpi('metro', update)
		cd ../../../Metro/data
	elseif strcmpi('cluster', update)
		cd ../../../Cluster/data
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
			filename = strcat(filename, 'binders');
			%Lets save away the heat capacities and magnisations
			tmp = load(filename);
			m2 = [m2 tmp(1)];
			m4 = [m4 tmp(2)];
			filename = '';
		end
		mag = [allRuns m2' m4'];
		m2 = [];
		m4 = [];
	end
	cd ../../plots/code/lab2
end
