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
     
    int b_size = nprocs*size;
    int array[size];
    
    for (int i=0;i<nprocs;i++)
    {   
        MPI_Barrier(MPI_COMM_WORLD);
        if (rank==i)
        {
            

            printf("\n rank (%d) origianl array:",rank);
            int index = 0;
            for (int i=rank*size;i<rank*size+size;i++)
            {
                array[index] = i+1;
                printf("%d , ",i+1);
                index = index+1;
            }
            
            printf("\n =========================== \n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
     
         
     
    int buffer_recv[b_size];
    rxtime = MPI_Wtime();
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(array, size, MPI_INT, buffer_recv,size, MPI_INT, 0,MPI_COMM_WORLD);
    txtime = MPI_Wtime();
    avgtime = txtime- rxtime;
     
      
        
    if (rank==0)
    {
         printf("\n rank (%d) receive array:",rank);
        for (int i=0;i<b_size;i++)
        {
            printf("%d , ",buffer_recv[i]);
            
        }
        
        printf("\n =========================== \n");
        printf("rank (%d) the avgtime is: %f \n",rank,avgtime); 
    }
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
