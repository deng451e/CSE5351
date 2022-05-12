
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int nprocs = -1;
    int rank = -1;
    
    int tag = 30;
    char processor_name[128];
    int namelen = 128;
    double txtime,rxtime,overhead,avgtime;
    double timebuffer = 0;
    int size = atoi(argv[2]);
     
    int array[size];
     
    double elapsed_time,begin_time,end_time;


    /* init */
    MPI_Init (&argc, &argv);
    begin_time =MPI_Wtime();
    MPI_Barrier (MPI_COMM_WORLD);
     
    MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
     
    MPI_Get_processor_name (processor_name, &namelen);
     
    
    if (rank==0)
    {
      for (int i=0;i<size;i++)
      {
        array[i]=rank;
      } 
       
       
      rxtime = MPI_Wtime();
      MPI_Send (&array, size, MPI_INT, 1, tag, MPI_COMM_WORLD);
      
      //fflush (stdout);
    }
    {
      int src = (rank == 0) ? (nprocs - 1) : (rank - 1);
      MPI_Status status;
      int buffer_recv[size];
       
      MPI_Recv (&buffer_recv, size, MPI_INT, src, tag, MPI_COMM_WORLD,&status);
       
      txtime = MPI_Wtime();
      
      ///fflush (stdout);
    }
    if (rank!=0)
    {
      int dest = (rank == nprocs - 1) ? (0) : (rank + 1);
       
       
      MPI_Send (&array, size, MPI_INT, dest, tag, MPI_COMM_WORLD);
      
      //fflush (stdout);
    }
     

    avgtime = (txtime - rxtime) ;
      
    if (rank ==0)
    {
      printf("The  time is: %f \n",avgtime );
    }
    MPI_Finalize ();
  
}
