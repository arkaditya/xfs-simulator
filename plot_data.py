import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter
import sys

try:
    # for Python2
    from Tkinter import *   ## notice capitalized T in Tkinter 
except ImportError:
    # for Python3
    from tkinter import *   ## notice lowercase 't' in tkinter here

plt.ion()
file = sys.argv[1]
pullData = open(file,"r").read()
dataArray = pullData.split('\n')
xar = []
yar = []
for eachLine in dataArray:

	if len(eachLine)>1:
		x,y = eachLine.split(',')
		xar.append(x)	
		yar.append(long(y))


			    # plt.gca().cla() # optionally clear axes
plt.plot(xar, yar, marker='o')
plt.axis('equal')
plt.title('No of Files Modified at hourly basis 10GB ')
plt.xlabel('Hours')
plt.ylabel('FilesModified')
plt.grid()
plt.legend("FilesModified")
		#ax = plt.gca()
		#ax.get_xaxis().set_major_formatter(ScalarFormatter())
plt.draw()
#plt.pause(0.1)

plt.show(block=True) # block=True lets the window stay open at the end of the animation.