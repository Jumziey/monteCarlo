close all; clear all;
format long;

tc = 2.269;
beta = 0.125;

sizes = [16 32 64 128 256];
temps = [2.20 2.22 2.24 2.25 2.26 2.265 2.266 2.267 2.268 2.269 2.27 2.271 2.272 2.275 2.28 2.285 2.29 2.30 2.31 2.32 2.34];
nsamp = 1000;
nblock = 64;
ntherm = 1000;
seed = 0;

allRuns = readData('cluster', sizes, temps, ntherm, nblock, nsamp, seed);
mag = readBinders('cluster', sizes, temps, ntherm, nblock, nsamp, seed);

t = temps-tc;
for i=1:size(mag,2)/2
	b(:,i) = mag(:,i*2-1).^2./mag(:,i*2);
end


plotstyle = {'x-' 'd-' 'o-' 's-' '+-'};
for i=1:length(sizes)
	hold on
	plot(temps,b(:,i), char(plotstyle(i)))
end
ylabel('Q_L')
xlabel('T')
title('Binders Cumulant vs Temp')

figure(2)
for i=1:length(sizes)
	hold on
	plot(t*sizes(i),b(:,i), char(plotstyle(i)))
end
ylabel('Q_L')
xlabel('(T-T_C)*L^{1/\nu}')
title('Binders Cumulant vs Scaled temp length')




legend('L=16', 'L=32', 'L=64', 'L=128', 'L=256')




