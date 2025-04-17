from mpi4py import MPI
import os

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

# Each rank spawns one worker
intercomm = MPI.COMM_SELF.Spawn(
    "./worker",  # Executable name
    args=[],  # Arguments for the worker program
    maxprocs=1
)

universe_size=MPI.COMM_WORLD.Get_attr(MPI.UNIVERSE_SIZE)

print(f"Hello from Python: {rank} / {size} - {universe_size}")

# Merge communicators to allow worker-worker communication
merged_comm = intercomm.Merge()
#merged_rank = merged_comm.Get_rank()
#merged_size = merged_comm.Get_size()

#print(f"Rank {rank} (Python) merged with Rank {merged_rank} (C worker) in new communicator of size {merged_size}")

# Send message from Python to C workers
#if rank == 0:
#    data = [rank] * size
#    merged_comm.Send(data, dest=rank + 1, tag=1)
#    print("Python rank 0 sent data to C workers")

# Receive data in C workers
#if merged_rank == rank + 1:
#    received_data = [0] * size
#    merged_comm.Recv(received_data, source=0, tag=1)
#    print(f"Worker {merged_rank} received: {received_data}")

merged_comm.Disconnect()
intercomm.Disconnect()
MPI.Finalize()
