close all; clear all;

%Defining what values to read
sizes = [8 16 32 64];
temps = [2 2.1 2.16 2.18 2.2 2.22 2.24 2.25 2.26 2.27 2.28 2.29 2.3 2.32 2.34 2.36 2.38 2.4 2.44 2.48 2.52 2.6 2.7];
nblock=1024;
nsamp=1000;
seed=0;

keys = {'L' 't' 'ntherm' 'nblock' 'nsamp' 'seed'};
vals = [0 0 0 nblock nsamp seed];

allRuns = readData('metro', sizes, temps, 0, nblock, nsamp, seed);

%Magnisation
%L=8
plot(temps,allRuns(:,3), 'xb-')
hold on
%16
plot(temps,allRuns(:,3+3*1),'o-', 'color', [1 .5 0])
%32u
plot(temps,allRuns(:,3+3*2),'g.-')
%64
plot(temps,allRuns(:,3+3*3),'*r-')
xlabel('Temperature (K)')
ylabel('Magnisation')
title('Magnisation vs Temperature')
legend('L=8', 'L=16', 'L=32', 'L=64')


%Heat capacity
figure(2)
%L=8
plot(temps,allRuns(:,2), 'xb-')
hold on
%16
plot(temps,allRuns(:,2+3*1),'o-', 'color', [1 .5 0])
%32
plot(temps,allRuns(:,2+3*2),'g.-')
%64
plot(temps,allRuns(:,2+3*3),'*r-')
xlabel('Temperature (K)')
ylabel('Heat capacity')
title('Heat capacity vs Temperature')
legend('L=8', 'L=16', 'L=32', 'L=64', 'Location', 'northwest')
