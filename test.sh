#!/bin/bash

for i in `seq 1 10`;
do
    for j in `seq 0.5 0.5 5`;
    do
        ./runSim $i $j 10
#         echo -e $i '\t' $j
    done
done
