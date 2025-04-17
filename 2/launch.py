import ctypes
from mpi4py import MPI


comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

print(f"Hello from Python: {rank} / {size}")

# Load the shared library
mylib = ctypes.CDLL("./mylib.so")

# Call the C++ function with no arguments
mylib.say_hello()

# Call a function with arguments
#mylib.add.argtypes = (ctypes.c_int, ctypes.c_int)  # Define argument types
#mylib.add.restype = ctypes.c_int  # Define return type
#result = mylib.add(5, 10)
#print("Result:", result)


comm_handle = comm.py2f()  # Convert communicator to an integer handle

mylib.mpi(comm_handle)
