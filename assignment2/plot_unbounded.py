#! /usr/bin/env python

import pylab

folder = "output/"

filelist = [(folder + "U1.txt", "1 ms"), 
            (folder + "U2.txt", "2 ms"), 
            (folder + "U3.txt", "3 ms")]

datalist = [(pylab.loadtxt(filename), label) for filename, label in filelist]
x_axis = pylab.np.linspace(-1, 1, datalist[0][0].size)

pylab.figure()
pylab.plot(pylab.loadtxt(folder + "U0.txt"), 'x', label="Initial condition")
pylab.grid()
pylab.legend()
pylab.show()

pylab.figure()
for data, label in datalist:
    pylab.plot(x_axis, data, 'x', label=label)

pylab.grid()
pylab.legend()
pylab.show()
