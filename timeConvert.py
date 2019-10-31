import time
import os
import datetime

fout = open('TimeFormatted_Data','a+')

with open('ExtractData_1','r') as file:
	for line in file:
		line = line.split(" ")
		access_time = datetime.datetime.fromtimestamp(float(line[11])).strftime('%c')
		last_mod_time = datetime.datetime.fromtimestamp(float(line[12])).strftime('%c')
		change_time = datetime.datetime.fromtimestamp(float(line[14])).strftime('%c')
		temp = line[0] + "\t" + access_time + "\t" + last_mod_time + "\t" + line[13] + "\t" + change_time + "\t" + line[15]
		fout.write(temp)

file.close()
fout.close()

