#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>
#include <float.h>
#include <math.h>

#define MULTIPLIER 1

double dtime() {
  double tseconds = 0.0;
  struct timeval mytime;
  gettimeofday(&mytime,(struct timezone*)0);
  tseconds = (double)(mytime.tv_sec + mytime.tv_usec*1.0e-6);
  return( tseconds );
}

int main(int argc, char *argv[]) {
  double tstart, tstop;
  int rank, size;
  MPI_Status status;
  long total = pow(10, MULTIPLIER);
  float add = 1.0/total;
  float buf = 0;
  /* Init */
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int sum = 0;
  
  tstart = dtime();
  for (int j = 0; j < 1; j++) {
    if (rank != 0) { // Slaves
      for (int i = 0; i <= total; i++) {
        buf += add;
        MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
      }
    } else { // Master
      int flag = -1;
      float res = 0;
      MPI_Request request;

      while (1) { 
        if(flag != 0) {
  //        printf("%d\n", status.MPI_SOURCE);
          MPI_Irecv(&res, 1, MPI_FLOAT, 1, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
//          printf("%g %d\n", res, status.MPI_SOURCE);
          flag = 0;
        } 
        if (request != NULL)
          MPI_Test(&request, &flag, &status);
        if (flag != 0) {
          //if (res < 1.1 && res > 1) 
          //  printf("recv : %g, slave : %d\n", res, status.MPI_SOURCE);
          if (status.MPI_SOURCE != -1) 
            sum += 1;
          flag = -1;
        }
       // printf("%d\n", sum);
        
        if (sum == (size-1)*total + (size-1)) {
          printf("res : %g, %i \n", res, sum);
   //       sum = 0;
          res = 0;
          break;
        } 
      }
    } 
  }
  MPI_Finalize();
  tstop = dtime();
    
  //if (rank == 0) 
   printf("Secs Serial = %10.3lf\n", tstop - tstart);
  
  return 0;
}
