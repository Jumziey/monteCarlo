import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

import plot

systems =[
        {
            'length': 32, 
            'marker': "g*", 
            'cutoff': 3e2,
        },
        {
            'length': 64, 
            'marker': "yd", 
            'cutoff': 1e3,
        }, 
        {
            'length': 128, 
            'marker': "rx", 
            'cutoff': 9e3,
        },
        {
            'length': 256, 
            'marker': "b.", 
            'cutoff': 3e4,
        }
]
binsize = 100

legends = []
for s in systems:
    plot.Avalanche('Size', s['length'], s['cutoff'], binsize, s['marker'], 1)
    legends.append("Length: " + str(s['length']))

#Legend
plt.legend(legends)

#Styling
plt.style.use('bmh')
plt.ylabel("Number of occurances")
plt.xlabel("Avalanche Size")
plt.title("Avalanche sizes in a sandpile\n of different sizes")
plt.tight_layout()
plt.ylim(10, 1e5)
plt.xlim(100,1e5)

plt.savefig("../report/figures/sizes.pdf")
plt.show()



