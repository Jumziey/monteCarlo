close all; clear all;
format long;
L = 32;
nsamp = 200;
temps = [1.8 2.0 2.2 2.3 2.4 2.6 2.8];
nblock = 12800;
seed = 0;



tcorr = readTimeCorr('metro', L, temps, 0, nblock, nsamp, seed)
time = linspace(0,200,200)';

figure(1)
for i = 1:length(temps)
	hold on
	plot(time(1:end),tcorr(1:end,i))
end
legend('T=1.8', 'T=2.0', 'T=2.2', 'T=2.3', 'T=2.4', 'T=2.6', 'T=2.8');
title('Time Correlation - Metropolis')
xlabel('Time - update')
ylabel('Normalized Correlation to t_0')

tcorr = readTimeCorr('cluster', L, temps, 0, nblock, nsamp, seed)

figure(2)
for i = 1:length(temps)
	hold on
	plot(time(1:end),tcorr(1:end,i))
end
legend('T=1.8', 'T=2.0', 'T=2.2', 'T=2.3', 'T=2.4', 'T=2.6', 'T=2.8');
title('Time Correlation - Wolff Cluster')
xlabel('Time - update')
ylabel('Normalized Correlation to t_0')
