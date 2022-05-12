#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
  
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    
    int nprocs = -1;
    int rank = -1;
    double txtime,rxtime,avgtime;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size = atoi(argv[2]);
     
    int array[size];
    for (int i=0;i<size;i++)
    {
      array[i]=rank;
    }

     
    int buffer_recv[size*(nprocs)];
    rxtime = MPI_Wtime();
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Alltoall(&array, size, MPI_INT, buffer_recv,size, MPI_INT, MPI_COMM_WORLD);
    txtime = MPI_Wtime();
    avgtime = txtime- rxtime;
     
    if (rank==0)
    {   
        printf("the time is: %f \n",avgtime); 
    }
    
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
