close all; clear all;
%Defining what values to read

L = 16;
temps = [2 2.1 2.2];
ntherm=L.^2;
nblock=64;
nsamp=10000;
seed=0;

data = readData('metro', L, temps, ntherm, nblock, nsamp, seed);
eSim = data(:,1);
cSim = data(:,2);

%Taking the heat capacity as defined in the lab instructions
tEq = [2.05 2.15];
cEq = [(eSim(2)-eSim(1))/(temps(2)-temps(1)) (eSim(3) - eSim(2))/(temps(3)-temps(2))];


plot(temps,cSim, 'x')
hold on
plot(tEq, cEq', 'o', 'color', [1 .5 0])
axis([1.95 2.25 0.7 1.4])
title('Heat capacity check')
legend('Calculated in simulation', 'Calculated by hand from energies at the different points','Location', 'northwest')
xlabel('Temperature')
ylabel('Heat Capacity')
