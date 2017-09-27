import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

import plot

systems =[
        {
            'length': 32, 
            'marker': "g*", 
            'cutoff': np.inf,
        },
        {
            'length': 64, 
            'marker': "yd", 
            'cutoff': np.inf,
        }, 
        {
            'length': 128, 
            'marker': "rx", 
            'cutoff': np.inf,
        },
        {
            'length': 256, 
            'marker': "b.", 
            'cutoff': np.inf,
        }
]
binsize = 50

legends = []
for s in systems:
    plot.Avalanche('Size', s['length'], s['cutoff'], binsize, s['marker'], 1)
    legends.append("Length: " + str(s['length']))

#Legend
plt.legend(legends)

#Styling
plt.style.use('fivethirtyeight')
plt.ylabel("Number of occurances")
plt.xlabel("Avalanche Size")
plt.title("Avalanche sizes in a sandpile\n of different sizes\n With all values included!")
plt.ylim(ymax=np.power(10,5))
#plt.xlim(100,np.power(10,5))
plt.tight_layout()

plt.savefig("../report/figures/valueanalysis.svg")
plt.show()



