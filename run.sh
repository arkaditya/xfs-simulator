#!/bin/bash

g++ -std=c++11 -g -pthread -o Simulator_new.out Simulator_new.cpp
sync
sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'
echo -e " 10GB Dumps "
./Simulator_new.out -m ~/Formatted_10G >> AccessTIme_10GB.log

sync
sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'

echo -e " 50GB Dumps "
./Simulator_new.out -m ~/Formatted_50G >> AccessTime_50GB.log


