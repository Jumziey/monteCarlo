close all; clear all;

%Defined in book
Tc = 2.269;

%Defining what values to read
sizes = [256];
temps = [2.2 2.22 2.24 2.25 2.255 2.26 2.262 2.266 2.268 2.269];
nblock=64;
nsamp=10000;
seed=0;

data256 = readData('cluster', sizes, temps, 1000, nblock, nsamp, seed)

sizes = [1024];
temps1024 = [2.265 2.266 2.267 2.269];
nblock=64;
nsamp=10000;
seed=0;

data1024 = readData('cluster', sizes, temps, 1000, nblock, nsamp, seed)

plot(data256(:,3),tc-temps)
hold on
plot(data1024(:,3),tc-temps1024)
