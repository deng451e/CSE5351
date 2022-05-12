#!/bin/bash


mpicc q3.c
ibrun -np 8 ./a.out 8 100000 


mpicc q3_opt.c
ibrun -np 8 ./a.out 8 100000 