#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) 
{
    int i;
    int n;
    int index;
    int size;
    int prime;
    int count;
    int global_count;
    int first;
    long int high_value;
    long int low_value;
    int rank;
    int nprocs;
    char * marked;
    double runtime;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    
    MPI_Barrier(MPI_COMM_WORLD);
    runtime = -MPI_Wtime();
    
    
    if (argc != 3)
    {
        if (rank == 0) 
            printf("Please enter an range.\n");
        MPI_Finalize();
        exit(1);
        
    }
    
    n = atoi(argv[2]);
    

    if ((3 +2*(((n - 1) / nprocs)-1)) < (int) sqrt((double) 2+2*(n-1)))
    {
        if (rank == 0)
            printf("Too many processes.\n");
        MPI_Finalize();
        exit(1);
    }
    int m = n;
    n =(n%2==0)?(n/2-1):((n-1)/2);
     
    low_value  = 3 + 2*(rank*(n)/nprocs);
    high_value = 3 + 2*((rank+1)*(n)/nprocs-1);
    size = (high_value - low_value)/2 + 1;
    //printf("rank(%d),%d,%d.%d \n",rank,low_value,high_value,size);
    marked = (char *) calloc(size, sizeof(char));
     
    if (marked == NULL) 
    {
        printf("Cannot allocate enough memory.\n");
        MPI_Finalize();
        exit(1);
    }
   
    if (rank == 0) 
        index = 0;
    prime = 3;
    if (rank==0)
    {
        printf("\n prime numbers: 2,");
    }
    do 
    {
        if (prime * prime > low_value) 
        {
            first = (prime * prime - low_value)/2;
        } 
        else 
        {
            if ((low_value % prime) == 0) 
                first = 0;
            else 
                first=((prime-low_value%prime)%2==0)?((prime-low_value%prime)/2):((prime-low_value%prime+prime)/2);
        }
        
        for (i = first; i < size; i += prime) 
        {
            marked[i] = 1;
             
        }
        if (rank == 0) 
        {
            while (marked[++index]);
                prime = 2*index + 3;
            
        }
    
        
        if (nprocs > 1) 
            MPI_Bcast(&prime,  1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    while (prime * prime <= 3+2*(n-1));
    
    count = 0;
    
    for (i = 0; i < size; i++)
    {
          if (marked[i] == 0) 
          {
                count++; 
                printf("%d,",i*2+low_value);
          }
    }
    if (nprocs > 1) 
    {
        MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    } 
    else 
    {
        global_count = count;
    }
    
    runtime += MPI_Wtime();
    
    if (rank == 0) 
    {
        printf("In %f seconds we found %d primes less than or equal to %d.\n",runtime, global_count+1, m);
    }
     
    MPI_Finalize();
    return 0;
}

