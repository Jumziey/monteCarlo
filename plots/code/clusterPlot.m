close all; clear all;

%Defined in book
tc = 2.269;

%Defining what values to read
sizes = [64];
temps = [2.2 2.22 2.24 2.25 2.255 2.26 2.262 2.266 2.268 2.269];
nblock=64;
nsamp=1000;
seed=0;

data64 = readData('cluster', sizes, temps, 0, nblock, nsamp, seed)

%Defining what values to read
sizes = [256];

data256 = readData('cluster', sizes, temps, 0, nblock, nsamp, seed)

sizes = [1024];
temps1024 = [2.265 2.266 2.267 2.268 2.269];
nblock=64;
nsamp=1000;
seed=0;

data1024 = readData('cluster', sizes, temps1024, 0, nblock, nsamp, seed)

nsamp=1;

loglog(tc-temps,(data64(:,3)))
hold on
loglog(tc-temps,(data256(:,3)))
hold on
loglog(tc-temps1024,(data1024(:,3)))
legend('64','256', '1024')
