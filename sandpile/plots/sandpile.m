close all; clear all;
L=64;
a=100000;


filename = '../../../sandpile/data/L';
filename = strcat(filename, num2str(L));
filename = strcat(filename, 'a');
filename = strcat(filename, num2str(a));

data = load(filename);
S = data(:,1);
T = data(:,1);

% SIZE DISTROBUTION
bins = ceil(sqrt(max(S)-min(S)));
hist = zeros(bins,1);

%Creating Histogram
for s = S'
	ind = floor(s/bins)+1;
	hist(ind) = hist(ind)+1;
end
binval = (1:bins:max(S))';
if(length(binval) ~= length(hist)) 
	binval(end+1) = max(S);
end

%Normalize probability
hist = hist./sum(hist);

cutoff=0;
%First values are abit off
start=10;
loglog(binval(start:end-cutoff),binval(start:end-cutoff).*hist(start:end-cutoff))

% LENGTH DISTROBUTION
bins = ceil(sqrt(max(T)-min(T)));
histTime = zeros(bins,1);

%Creating Histogram
for t =T'
	ind = floor(t/bins)+1;
	histTime(ind) = histTime(ind)+1;
end
binval = (1:bins:max(S))';
if(length(binval) ~= length(histTime)) 
	binval(end+1) = max(S);
end

%Normalize probability
histTime = histTime./sum(histTime);

figure(2)
cutoff=0;
%First values are abit off
start=1;
loglog(binval(start:end-cutoff),histTime(start:end-cutoff))




%{
histogram(S, 'Normalization', 'probability');
Sd = fitdist(S,'exponential')

x = [0:0.1:10000];
y = exppdf(x,mean(Sd));
hold on
scale = 0.7/max(y);
plot(x,y.*scale);
%}
