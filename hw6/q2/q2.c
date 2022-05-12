
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
    int factor = atoi(argv[3]);
    
    double elapsed_time,begin_time,end_time;
     
    
     
    /* init */
    MPI_Init (&argc, &argv);
     
    MPI_Barrier (MPI_COMM_WORLD);
     
    MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
     
    MPI_Get_processor_name (processor_name, &namelen);
     
    
    int send_buff[size*nprocs];

    if (rank==0)
    {   printf("\n=========================== \n");
        for (int i=0;i<nprocs;i++)
        {
            printf("rank(%d) take array entry input \n",i);
            for (int j=0;j<size;j++)
            {
                int hold;
                printf("enter %d array entry: ",j+1);
                scanf("%d", &hold);
                send_buff[size*i+j]=hold;  
                
            }
            printf("=========================== \n");

        } 
        
    }
    MPI_Scatter(&send_buff, size, MPI_INT, array,size, MPI_INT, 0,MPI_COMM_WORLD);
    //===============================
    
    for (int i=0;i<nprocs;i++)
    {   
        if (rank==i)
        {
            

            printf("\n rank (%d) orignal array:",rank);
            
            for (int j=0;j<size;j++)
            {
            
                printf(" %d, ",array[j]);
                 
                 
            }    
            printf("\n =========================== \n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    } 
    //##############################################
    if( factor>0)
    {
        for (int i=0;i<factor;i++)
        {
            
            {
                int buffer[0];
                int dest = (rank == nprocs - 1) ? (0) : (rank + 1);
                buffer[0]=array[size-1];
                for(int j=size-1;j>0;j--)
                {   
                    
                    array[j]=array[j-1];
                    
                }
                
                MPI_Send (&buffer, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
                
                //fflush (stdout);
            }

            {
                int buffer[0];
                int src = (rank == 0) ? (nprocs - 1) : (rank - 1);
                MPI_Status status;
                
                MPI_Recv (&buffer, 1, MPI_INT, src, tag, MPI_COMM_WORLD,&status);
                
                array[0]=buffer[0];
                
                ///fflush (stdout);
            }
        }
        
    }
    else if(factor<0)
    {   
        factor = factor*(-1);
        for (int i=0;i<factor;i++)
        {
             
            {
                int buffer[0];
                int dest = (rank == 0) ? (nprocs - 1) : (rank - 1);
                buffer[0]=array[0];
                for(int j=0;j<size;j++)
                {   
                    
                    array[j]=array[j+1];
                    
                }
                
                MPI_Send (&buffer, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
                
                //fflush (stdout);
            }

            {
                int buffer[0];
                int src = (rank == nprocs - 1) ? (0) : (rank + 1);
                MPI_Status status;
                
                MPI_Recv (&buffer, 1, MPI_INT, src, tag, MPI_COMM_WORLD,&status);
                
                array[size-1]=buffer[0];
                
                ///fflush (stdout);
            }
        }
    }
    if (rank==0)
    {
         printf("\n shifting factor:%d \n",factor);
    }
        
    for (int i=0;i<nprocs;i++)
    {   
        MPI_Barrier(MPI_COMM_WORLD);
        if (rank==i)
        {
            

            printf("\n rank (%d) final array:",rank);
            
            for (int j=0;j<size;j++)
            {
                 
                printf("%d , ",array[j]);
                 
            }
            
            printf("\n =========================== \n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    

    MPI_Finalize ();
  
}
