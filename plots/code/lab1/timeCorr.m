close all; clear all;
format long;
L = 32;
nsamp = 200;
temps = [1.8 2.0 2.2 2.3 2.4 2.6 2.8];
nblock = 128;
seed = 0;

tcorr = readTimeCorr('metro', L, temps, 0, nblock, nsamp, seed)

time = linspace(0,200,200)';

plot(time(1:end),tcorr(1:end,7))
