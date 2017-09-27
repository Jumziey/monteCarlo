import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

figuredir = "../report/figures/"
datadir = "../data/"

def Avalanche(typeof, length, cutoff, binsize, marker, fig):

    data = loadAvalancheData(length)

    plt.figure(fig)

    #Size or Time
    hs = data[typeof]

    #Removing the largest avalanches (not statistically well represented in the data)
    hs = hs[hs.values<cutoff]

    #Creating histogram
    nrofbins = np.ceil(hs.max()/binsize)
    print("###########################");
    print("Length: "+ str(length))
    print("Actual nrofbins: " + str(hs.max()/binsize))
    print("hs.max():" + str(hs.max()))
    print("nrofbins: " + str(nrofbins))
    print("binsize: " + str(hs.max()/nrofbins))
    print("###########################");
    hs = hs.value_counts(bins=nrofbins)
    
    #Removing bins without any occurance
    hs = hs[hs.values != 0]

    #Balancing histogram to the "middle value"
    hs.index = hs.index + binsize/2

    return plt.loglog(hs, marker)
    

def styleAvalanche():
    plt.style.use('fivethirtyeight')

    plt.ylabel("Number of occurances")
    plt.xlabel("Avalanche "+typeof)
    plt.title("Sandpile with length L="+str(length)+"\n Avalanche "+typeof)

    plt.tight_layout()
    plt.ylim(ymin=1)
    plt.xlim(1,np.power(10,5))

def loadAvalancheData(length):
    filename = datadir + "L" + str(length) + "a1000000"
    return pd.read_csv(filename, delimiter='\t')

