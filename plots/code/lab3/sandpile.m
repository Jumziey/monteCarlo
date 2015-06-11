close all; clear all;
L=64;
a=10000;


filename = '../../../sandpile/data/L';
filename = strcat(filename, num2str(L));
filename = strcat(filename, 'a');
filename = strcat(filename, num2str(a));

data = load(filename);
S = data(:,1);
t = data(:,1);

histogram(S, 'Normalization', 'probability');
Sd = fitdist(S,'exponential')

x = [0:0.1:10000];
y = exppdf(x,mean(Sd));
hold on
scale = 0.7/max(y);
plot(x,y.*scale);
