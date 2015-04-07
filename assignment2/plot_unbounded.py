#! /usr/bin/env python

import pylab

folder = "output/"
filelist = [(folder + "U0.txt", "init"), 
            (folder + "U1.txt", "1 ms"), 
            (folder + "U2.txt", "2 ms"), 
            (folder + "U3.txt", "3 ms")]

for filename, label in filelist:
    datalist = pylab.loadtxt(filename), label

x_axis = pylab.np.linspace(-1, 1, pylab.loadtxt(folder + "U0.txt").size)

for data, label in datalist:
    pylab.plot(x_axis, data, label=label)

pylab.grid()
pylab.legend()
pylab.show()
