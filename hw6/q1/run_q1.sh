#!/bin/bash


array_size=(8 16 32)
processor_num=(2 4 6 8 16)

mpicc q1_gather.c 
rm gather_results/*
for i in ${array_size[@]}; do
    for j in ${processor_num[@]}; do
         for _ in {1..10}; do 
            ibrun -np $j ./a.out $j $i | grep avgtime >> "gather_results/$i.log"
        done 
        echo "--------------------------" >> "gather_results/$i.log"
        echo $i
    done
done



mpicc q1_scatter.c 
rm scatter_results/*
for i in ${array_size[@]}; do
    for j in ${processor_num[@]}; do
         for _ in {1..10}; do 
            ibrun -np $j ./a.out $j $i | grep avgtime >> "scatter_results/$i.log"
        done 
        echo "--------------------------" >> "scatter_results/$i.log"
        echo $i
    done
done



