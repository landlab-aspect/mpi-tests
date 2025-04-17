#include <mpi.h>

#include <iostream>

extern "C" {  // Ensure C-style linking
    void say_hello() {
      //std::cout << "Hello from C++!" << std::endl;
    }

    void mpi(int comm_handle) {
    
	MPI_Comm comm = MPI_Comm_f2c(comm_handle);  // Convert integer handle to MPI_Comm

    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    printf("Hello from C++! Rank: %d, Size: %d\n", rank, size);
    
    }
  
    int add(int a, int b) {
        return a + b;
    }
}
