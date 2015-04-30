#! /usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

t, x = np.loadtxt('trajectory.txt', delimiter='\t', unpack='true')

plt.plot(x, t)
plt.xlabel('x')
plt.ylabel('t')
plt.xlim([-np.max(np.abs(x))-0.5, np.max(np.abs(x))+0.5])
plt.grid()
plt.show()
