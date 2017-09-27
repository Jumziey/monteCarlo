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
    print("nrofbins: " + str(nrofbins))
    print("Actual nrofbins: " + str(hs.max()/binsize))
    print("binsize: " + str(binsize))
    print("Actual binsize: " + str(hs.max()/nrofbins))
    print("###########################");
    hs = hs.value_counts(bins=nrofbins)
    
    #Removing bins without any occurance
    hs = hs[hs.values != 0]

    #Balancing histogram to the "middle value"
    hs.index = hs.index + binsize/2

    plt.loglog(hs, marker)
    return hs
    
def loadAvalancheData(length):
    filename = datadir + "L" + str(length) + "a1000000"
    return pd.read_csv(filename, delimiter='\t')

