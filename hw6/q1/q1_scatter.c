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
    int b_size = atoi(argv[2]);
    int size = b_size*nprocs;
     
    int array[size];
    
    if (rank==0)
    {   
        printf("orginal arrray: ");
        for (int i=0;i<size;i++)
        {
            array[i]=i+1;
            printf("%d , ",i+1);
        }
        printf("\n");
    }
     
    int buffer_recv[b_size];
    rxtime = MPI_Wtime();
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatter(array, b_size, MPI_INT, buffer_recv,b_size, MPI_INT, 0,MPI_COMM_WORLD);
    txtime = MPI_Wtime();
    avgtime = txtime- rxtime;
     
     
    MPI_Barrier(MPI_COMM_WORLD);
    // ; 
    for (int i=0;i<nprocs;i++)
    {   
        MPI_Barrier(MPI_COMM_WORLD);
        if (rank==i)
        {
            

            printf("\n rank (%d) receive array:",rank);
            for (int i=0;i<b_size;i++)
            {
                printf("%d , ",buffer_recv[i]);
                
            }
            
            printf("\n =========================== \n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    if (rank==0)
    {
        printf("rank (%d) the avgtime is: %f \n",rank,avgtime); 
    }
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
