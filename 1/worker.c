#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  MPI_Comm parent, merged_comm;
  int rank, size, merged_rank, merged_size;

  MPI_Init(&argc, &argv);
  MPI_Comm_get_parent(&parent);
  if (parent == MPI_COMM_NULL) {
    printf("No parent! Exiting...\n");
    MPI_Finalize();
    return 1;
  }

  {

    MPI_Comm_rank(parent, &rank);
    MPI_Comm_size(parent, &size);

    printf("Worker Rank %d of size %d\n", rank, size);
  }

  // Merge with Python ranks
  MPI_Intercomm_merge(parent, 1, &merged_comm);
  MPI_Comm_rank(merged_comm, &merged_rank);
  MPI_Comm_size(merged_comm, &merged_size);

  printf("Worker Rank %d in merged communicator of size %d\n", merged_rank,
         merged_size);

  // Exchange data between workers
  /*    if (merged_rank == 1) {
      int data = 100;
      MPI_Send(&data, 1, MPI_INT, 2, 0, merged_comm);
      printf("Worker 1 sent %d to Worker 2\n", data);
  } else if (merged_rank == 2) {
      int received_data;
      MPI_Recv(&received_data, 1, MPI_INT, 1, 0, merged_comm,
  MPI_STATUS_IGNORE); printf("Worker 2 received: %d\n", received_data);
      }*/

  MPI_Comm_free(&merged_comm);
  MPI_Finalize();
  return 0;
}
