cmake_minimum_required(VERSION 3.10)
project(mpitest)

# Find MPI
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Find Python
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Add Executable
add_executable(main main.cc)
target_link_libraries(main ${MPI_LIBRARIES} ${Python3_LIBRARIES})

# Enable MPI
if(MPI_COMPILE_FLAGS)
    set_target_properties(main PROPERTIES COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(main PROPERTIES LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
