import matplotlib.pyplot as plt
import csv
import sys
import numpy as np

plt.ion()
file = sys.argv[1]
pullData = open(file,"r").read()
dataArray = pullData.split('\n')
xar = []
yar = []
for eachLine in dataArray:

	if len(eachLine)>1:
		x,y,z = eachLine.split(',')
		xar.append(x)	
		yar.append(float(z))

plt.figure()
			    # plt.gca().cla() # optionally clear axes
plt.plot(xar, yar, marker='o')
plt.axis('equal')
plt.title('No of Files Modified at hourly basis 10GB ')
plt.xlabel('Hours')
plt.ylabel('FilesModified')
plt.grid(True)
plt.legend("FilesModified")
plt.show()
