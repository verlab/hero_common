import numpy as np
import pylab
from scipy.optimize import curve_fit
import sys

filename = sys.argv[1]

data = np.load(filename)
xdata = data[:,0]
ydataL = data[:,1]
ydataR = data[:,3]
pylab.plot(ydataL, xdata, 'o', alpha=0.1, label='Data Motor Left')
pylab.plot(ydataR, xdata, 'o', alpha=0.1, label='Data Motor Right')

def fsigmoid(x, a, b):
    return 1.0 / (1.0 + np.exp(-a*(x-b)))

def sigmoid(x, L ,x0, k, b):
    y = L / (1 + np.exp(-k*(x-x0)))+b
    return (y)

def invsigmoid(y, L ,x0, k, b):
    x = - np.log(L/(y-b) - 1.0)/k + x0
    return (x)

       
p0 = [max(-ydataL), np.median(xdata),1,min(-ydataL)]
popt, pcov = curve_fit(sigmoid, xdata, -ydataL,p0, method='dogbox')
print("\33[94mParameter Motor Left: {:f} {:f} {:f} {:f}\33[0m".format(popt[0], popt[1], popt[2], popt[3]))
vel = np.linspace(-0.4, 0.4, 1000)
pwm = invsigmoid(-vel, *popt)
pylab.plot(vel,pwm, label='fit Motor Left')
print("\33[92mTest vel: 0.105847 -> pwm: {:f}\33[0m".format(invsigmoid(-0.105847, *popt)))


p0 = [max(ydataR), np.median(xdata),1,min(ydataR)]
popt, pcov = curve_fit(sigmoid, xdata, ydataR,p0, method='dogbox')
print("\33[94mParameter Motor Right: {:f} {:f} {:f} {:f}\33[0m".format(popt[0], popt[1], popt[2], popt[3]))
vel = np.linspace(-0.4, 0.4, 1000)
pwm = invsigmoid(vel, *popt)
pylab.plot(vel,pwm, label='fit Motor Right')
print("\33[92mTest vel: 0.105847 -> pwm: {:f}\33[0m".format(invsigmoid(0.105847, *popt)))

pylab.legend(loc='best')
pylab.show()