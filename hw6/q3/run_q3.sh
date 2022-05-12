#!/bin/bash


range=(100000 1000000 10000000)
processor_num=(2 4 8 16 32)
 
mpicc q3.c 
rm q3_results/*
for i in ${range[@]}; do
    for j in ${processor_num[@]}; do
         for _ in {1..10}; do 
            ibrun -np $j ./a.out $j $i | grep seconds >> "q3_results/$i.log"
        done 
        echo "--------------------------" >> "q3_results/$i.log"
        echo $i
    done
done



mpicc q3_opt.c 
rm q3opt_results/*
for i in ${range[@]}; do
    for j in ${processor_num[@]}; do
         for _ in {1..10}; do 
            ibrun -np $j ./a.out $j $i | grep seconds >> "q3opt_results/$i.log"
        done 
        echo "--------------------------" >> "q3opt_results/$i.log"
        echo $i
    done
done


