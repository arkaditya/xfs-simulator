#!/bin/bash

g++ -std=c++11 -g -pthread -o Simulator_new.out Simulator_new.cpp
sync
sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'
echo -e " 10GB Dumps "
#./Simulator_new.out -m ~/Formatted_10G Index_Time_FormattedData_10G.log 
python3 plot_discrete.py Index_Time_FormattedData_10G.log >> index_time_output_10G

sync
sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'

echo -e " 50GB Dumps "
#./Simulator_new.out -m ~/Formatted_50G Index_Time_FormattedData_50G.log 
python3 plot_discrete.py Index_Time_FormattedData_50G.log >> index_time_output_50G


