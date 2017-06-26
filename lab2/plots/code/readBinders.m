function mag = readData(sizes, temps, ntherm, nblock, nsamp, seed)

	keys = {'L' 't' 'ntherm' 'nblock' 'nsamp' 'seed'};
	vals = [0 0 0 nblock nsamp seed];

	filename='';

	m2 = [];
	m4 = [];
	mag = [];
	
	cd ../../data

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
		mag = [mag m2' m4'];
		m2 = [];
		m4 = [];
	end

	cd ../plots/code
end
