close all; clear all;

%Defined in book
tc = 2.26919;

%Defining what values to read
sizes = [64];
temps = [2.2 2.22 2.24 2.25 2.255 2.26 2.262 2.266 2.268 2.269];
nblock=128;
nsamp=1000;
seed=0;

data64 = readData('cluster', sizes, temps, 1000, nblock, nsamp, seed);

%Defining what values to read
sizes = [256];
nsamp=1000;

data256 = readData('cluster', sizes, temps, 1000, nblock, nsamp, seed);

sizes = [1024];
temps1024 = [ 2.24 2.25 2.255 2.26 2.262 2.265 2.266 2.267 2.268 2.269];
nblock=64;
nsamp=1000;

data1024 = readData('cluster', sizes, temps1024, 1000, nblock, nsamp, seed);

tctemps = tc-temps;
tctemps1024 = tc-temps1024;

loglog(tctemps,(data64(:,3)),'o:')
hold on
loglog(tctemps,(data256(:,3)),'x:')
hold on
loglog(tctemps1024,(data1024(:,3)),'d:')

p = polyfit(log(tctemps1024(1:6)'), log(data1024(1:6,3)), 1);

loglog(tctemps, tctemps.^p(1)*exp(p(2)), 'g-')

legend('64','256', '1024', 'Linear fit', 'Location', 'northwest')

disp(sprintf('BETA = %16f', p(1)));

xlabel('(Tc - Temp) (k)')
ylabel('|m|')
