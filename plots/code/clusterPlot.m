close all; clear all;

%Defined in book
Tc = 2.269;

%Defining what values to read
sizes = [256];
temps = [2.2 2.22 2.24 2.25 2.255 2.26 2.262 2.264 2.266 2.268 2.269];
nblock=1;
nsamp=10000;
seed=0;

data256 = readData('cluster', sizes, temps, ntherm, nblock, nsamp, seed)

sizes = [256];
temps = [2.2 2.22 2.24 2.25 2.255 2.26 2.262 2.264 2.266 2.268 2.269];
nblock=1;
nsamp=10000;
seed=0;

data1024 = readData('cluster', sizes, temps, ntherm, nblock, nsamp, seed)

fitFunc = @(b) (tcnr
