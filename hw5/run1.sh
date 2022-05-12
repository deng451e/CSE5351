#!/bin/bash


for i in {1..100}; do 
    ibrun  -np 2  ./a.out 2  64 >> q1_64.log 
    
done
echo "--------------------------" >> q1_64.log 

for i in {1..100}; do 
    ibrun  -np 4  ./a.out 4  64 >> q1_64.log 
     
done

echo "--------------------------" >> q1_64.log 
for i in {1..100}; do 
    ibrun  -np 8 ./a.out 8  64 >> q1_64.log 
     
done
echo "--------------------------" >> q1_64.log 

for i in {1..100}; do 
    ibrun  -np 16  ./a.out 16 64  >> q1_64.log 
     
done 
echo "--------------------------" >> q1_64.log 



for i in {1..100}; do 
    ibrun  -np 2  ./a.out 2  512 >> q1_512.log 
     
done

echo "--------------------------" >> q1_512.log


for i in {1..100}; do 
    ibrun  -np 4  ./a.out 4  512 >> q1_512.log
 
     
done
echo "--------------------------" >> q1_512.log
 

for i in {1..100}; do 
    ibrun  -np 8 ./a.out 8  512 >> q1_512.log
 
    
done
echo "--------------------------" >> q1_512.log

for i in {1..100}; do 
    ibrun  -np 16  ./a.out 16 512  >> q1_512.log
 
     
done
echo "--------------------------" >> q1_512.log
 