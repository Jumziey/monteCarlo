import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

import plot

s = {
        'length': 256, 
        'marker': "b.", 
        'cutoff': 1e4,
    }

binsize = 100

hs = plot.Avalanche('Size', s['length'], s['cutoff'], binsize, s['marker'], 1)

#fitting
#Removing first value since its off due to "wall contribution"
fit = hs[hs.index != hs.index[0]]
k = np.polyfit(np.log(fit.index), np.log(fit.values), 1)
plt.loglog(fit.index, np.exp(k[1] + np.log(fit.index)*k[0]), "r")

print("c: " + str(k[0]))


plt.legend(["Measured values of system\n(Length: " + str(s['length'])+")", "Fitted line"])

#Styling
plt.style.use('fivethirtyeight')
plt.ylabel("Number of occurances")
plt.xlabel("Avalanche Size")
plt.title("Avalanche sizes in a sandpile\n of different sizes\n Finding the power relation coefficient")
plt.tight_layout()
plt.ylim(1e2, 1e5)
plt.xlim(1e2,1e5)

plt.savefig("../report/figures/sizefit.svg")
plt.show()



