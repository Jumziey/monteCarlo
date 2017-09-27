import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

import plot

systems =[
        {
            'length': 32, 
            'marker': "g*", 
            'cutoff': 6e1,
        },
        {
            'length': 64, 
            'marker': "yd", 
            'cutoff': 2e2,
        }, 
        {
            'length': 128, 
            'marker': "rx", 
            'cutoff': 4e2,
        },
        {
            'length': 256, 
            'marker': "b.", 
            'cutoff': 1e3,
        }
]
binsize = 20

legends = []
for s in systems:
    plot.Avalanche('Time', s['length'], s['cutoff'], binsize, s['marker'], 1)
    legends.append("Length: " + str(s['length']))

#Legend
plt.legend(legends)

#Styling
plt.style.use('bmh')
plt.ylabel("Number of occurances")
plt.xlabel("Avalanche time")
plt.title("Avalanche times in a sandpile\n of different sizes")
plt.tight_layout()
plt.ylim(ymax=3e5)
plt.xlim(xmin=2e1)

plt.savefig("../report/figures/times.pdf")
plt.show()



