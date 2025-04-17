#include <mpi.h>
#include <Python.h>
#include <iostream>

void call_python_function(int comm_handle) {
    // Initialize Python
    Py_Initialize();
    PyRun_SimpleString("import sys; sys.path.append(\".\")");

    // Import Python module
    PyObject* pModule = PyImport_ImportModule("child");
    if (!pModule) {
        std::cerr << "Failed to load Python module" << std::endl;
        Py_Finalize();
        return;
    }

    // Get function from module
    PyObject* pFunc = PyObject_GetAttrString(pModule, "mpi_function");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        std::cerr << "Failed to load function" << std::endl;
        Py_DECREF(pModule);
        Py_Finalize();
        return;
    }

    // Call Python function with communicator handle
    PyObject* pArgs = PyTuple_Pack(1, PyLong_FromLong(comm_handle));
    PyObject* pValue = PyObject_CallObject(pFunc, pArgs);

    // Clean up
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);

    // Finalize Python
    Py_Finalize();
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;
    int comm_handle = MPI_Comm_c2f(comm);  // Convert communicator to integer handle

    int rank;
    MPI_Comm_rank(comm, &rank);
    if (rank == 0) {
        std::cout << "C++: Calling Python function..." << std::endl;
    }

    call_python_function(comm_handle);

    MPI_Finalize();
    return 0;
}
