close all; clear all;
format long;

tc = 2.269;
beta = 0.125;

sizes = [16 32 64 128 256];
temps = [2.20 2.22 2.24 2.25 2.26 2.265 2.266 2.267 2.268 2.269 2.27 2.271 2.272 2.275 2.28 2.285 2.29 2.30 2.31 2.32 2.34 2.36 2.38 2.40 2.44 2.48];
nsamp = 1000;
nblock = 32;
ntherm = 1000;
seed = 0;

allRuns = readData('cluster', sizes, temps, ntherm, nblock, nsamp, seed);

plotstyle = {'x-' 'd-' 'o-' 's-' '+-'};
for i=1:length(sizes)
	hold on
	plot(temps,allRuns(:,i*3), char(plotstyle(i)))
end
legend('L=16', 'L=32', 'L=64', 'L=128', 'L=256')
xlabel('Temperature (K)')
ylabel('|m|')
title('m vs T')

figure(2)
for i=1:length(sizes)
	hold on
	plot(temps,allRuns(:,i*3)*sizes(i).^beta, char(plotstyle(i)))
end
legend('L=16', 'L=32', 'L=64', 'L=128', 'L=256')
xlabel('Temperature (K)')
ylabel('mL^{\beta/\nu}')
title('mL^{\beta/\nu} vs T')

figure(3)
t = temps-tc;
plotstyle = {'x' 'd' 'o' 's' '+'};
for i=1:length(sizes)
	hold on
	plot(t*sizes(i),allRuns(:,i*3)*sizes(i).^beta, char(plotstyle(i)))
end
legend('L=16', 'L=32', 'L=64', 'L=128', 'L=256')
xlabel('tL^{1/\nu}')
ylabel('mL^{\beta/\nu}')
title('mL^{\beta} vs tL^{1/\nu}')

figure(4)
for i=1:length(sizes)
	hold on
	plot(t*sizes(i),allRuns(:,i*3)*sizes(i).^beta, char(plotstyle(i)))
end
axis([-0.25 0.25 0.85 1])
legend('L=16', 'L=32', 'L=64', 'L=128', 'L=256')
xlabel('tL^{1/\nu}')
ylabel('mL^{\beta/\nu}')
title('mL^{\beta} vs tL^{1/\nu}')
