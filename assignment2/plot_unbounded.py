#! /usr/bin/env python

import pylab

filelist = [("U0.txt", "init"), ("U1.txt", "1 ms"), 
            ("U5.txt", "5 ms"), ("U10.txt", "10 ms")]
datalist = [(pylab.loadtxt(filename), label) for filename, label in filelist]

for data, label in datalist:
    pylab.plot(data, label = label)

pylab.plot(data)
pylab.grid()
pylab.legend()
pylab.show()
