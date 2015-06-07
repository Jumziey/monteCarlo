close all; clear all;
format long;
L = 32;
nsamp = 200;
temps = [1.8 2.0 2.2 2.3 2.4 2.6 2.8];
nblock = 12800;
seed = 0;

% -2.2

tcorr = readTimeCorr('metro', L, temps, 0, nblock, nsamp, seed);
time = linspace(0,200,200)';


ends = [];
for i = 1:length(temps)
	j=1;
	while(log(tcorr(j,i)) > -2.5)
		j = j+1;
	end
	ends = [ends j-1];
end

	
corrtime = [];
figure(1)
for i = 1:length(temps)
	semilogy(time(1:ends(i)),tcorr(1:ends(i),i))
	p = polyfit(time(1:ends(i)), tcorr(1:ends(i),i),1);
	corrtime = [corrtime -1/p(1)];
	hold on
end
legend('T=1.8', 'T=2.0', 'T=2.2', 'T=2.3', 'T=2.4', 'T=2.6', 'T=2.8');
title('Time Correlation - Metropolis')
xlabel('Time - update')
ylabel('Normalized Correlation to t_0')

tcorr = readTimeCorr('cluster', L, temps, 0, nblock, nsamp, seed);

v(1,:) = temps;
v(2,:) = corrtime;
for i = 1:2
	for j = 1:length(temps)
		fprintf('%8f',v(i,j))
		if j ~= length(temps)
			fprintf(' & ')
		end
	end
	disp('\\')
	if i==1
		disp('\hline')
	end
end

figure(2)
for i = 4
	semilogy(time(1:100),tcorr(1:100,i))
	hold on
end

title('Time Correlation - Wolff Cluster, T=2.3')
xlabel('Time - update')
ylabel('Normalized Correlation to t_0')
