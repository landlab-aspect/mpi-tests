# C++/Python MPI coupling tests

- goal: how to write an MPI parallel code with Python and C++ (coupling two codes where both have access to MPI)?

## **EXPERIMENT1:** MPI_comm_spawn

- MPI_comm_spawn() can create new processes communicating with MPI:
- https://www.open-mpi.org/doc/v4.1/man3/MPI_Comm_spawn.3.php
- spawn with COMM_SELF: only talk to parent
- spawn with COMM_WORLD: can talk to each other, placement not specified
- MPI_comm_spawn can launch python from c (or other way)
- can not oversubscribe, UNIVERSE size (cores on the system)


## **EXPERIMENT2:** MPI launch Python, execute c code from shared lib:

- can pass MPI Comm, can duplicate and communicate globally

## **EXPERIMENT3:** MPI launch c++, execute Python code:

- need to link to libpython
- can load python module and execute functions
- can pass commuicator and communicate!

