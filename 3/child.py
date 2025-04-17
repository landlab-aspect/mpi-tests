from mpi4py import MPI

def mpi_function(comm_handle):
    # Convert the handle back to an MPI communicator
    comm = MPI.Comm.f2py(comm_handle)

    rank = comm.Get_rank()
    size = comm.Get_size()

    print(f"Python: Hello from Rank {rank} of {size}")

    data = 1
    globalsum = comm.allreduce(data, op=MPI.SUM)

    print(f"Python: sum {globalsum}")

