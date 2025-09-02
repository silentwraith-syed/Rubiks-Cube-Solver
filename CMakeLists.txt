cmake_minimum_required(VERSION 3.20)
project(rubiks_cube_solver)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV with specific components
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui videoio)

include_directories(Model)
include_directories(Scanner)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(rubiks_cube_solver
        Model/RubiksCube.cpp
        Model/RubiksCube.h
        main.cpp 
        Model/RubiksCube3dArray.cpp 
        Model/RubiksCube1dArray.cpp 
        Model/RubiksCubeBitboard.cpp 
        Solver/DFSSolver.h 
        Solver/BFSSolver.h 
        Solver/IDDFSSolver.h 
        Model/PatternDatabase/PatternDatabase.h 
        Solver/IDAstarSolver.h 
        PatternDatabases/NibbleArray.cpp 
        PatternDatabases/NibbleArray.h 
        PatternDatabases/PatternDatabase.cpp 
        PatternDatabases/PatternDatabase.h 
        PatternDatabases/PermutationIndexer.h 
        PatternDatabases/CornerPatternDatabase.cpp 
        PatternDatabases/CornerPatternDatabase.h 
        PatternDatabases/CornerDBMaker.cpp 
        PatternDatabases/CornerDBMaker.h 
        PatternDatabases/math.cpp 
        PatternDatabases/math.h
        Scanner/CubeScanner.cpp
        Scanner/CubeScanner.h)

# Link OpenCV libraries using the proper CMake target
target_link_libraries(rubiks_cube_solver ${OpenCV_LIBS})

# Print debug info
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
