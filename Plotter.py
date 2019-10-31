import matplotlib.pyplot as pl
import numpy as np
import csv

X1 = []
Y1 = []
X2 = []
Y2 = []

# with open('Dec23_ModifiedFiles.csv','r') as csvfile:
# 	plots = csv.reader(csvfile,delimiter=',')
# 	for row in plots:
# 		X2.append(row[0])
# 		Y2.append(int(row[1]))

# #pl.plot(X1, Y1, label='Date v/s FileCount')
# pl.plot(X2, Y2 ,label='Modified Files per Hour')
# pl.xlabel("Hours")
# pl.ylabel("No of Files Modified")
# pl.legend()
# #pl.rcParams.update({'font.size':})
# pl.grid(True)
# for a,b in zip(X2,Y2):
# 	pl.text(a,b,str(b))
# pl.show()


with open('FileAccessTimes.csv','r') as csvfile:
	plots = csv.reader(csvfile,delimiter=',')
	for row in plots:
		X1.append(row[0])
		Y1.append(int(row[1]))

pl.plot(X1, Y1 ,label='Files Accessed per Day')
pl.xlabel("Date")
pl.ylabel("No of Files Accessed")
pl.legend()
#pl.rcParams.update({'font.size':})
pl.grid(True)
for a,b in zip(X1,Y1):
	pl.text(a,b,str(b))
pl.show()
