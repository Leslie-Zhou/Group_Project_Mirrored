# CMAKELISTS.TXT for model program
# This is the minimum cmake version
cmake_minimum_required( VERSION 2.8 )

# Name of the project
project( model )

# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Include the header and source folders.
include_directories (Test)
include_directories (Code)

# Include libraries
add_library( modellib Code/model.cpp Code/Material.cpp Code/Cell.cpp Code/vectorClass.cpp 
               	      Code/model.h Code/Material.h Code/Cell.h Code/vectorClass.h )

# Load the example mod files to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Example_Model_Files/ExampleModel1.mod 
	  ${CMAKE_CURRENT_SOURCE_DIR}/Example_Model_Files/ExampleModel2.mod 
          ${CMAKE_CURRENT_SOURCE_DIR}/Example_Model_Files/ExampleModel3.mod
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Define the executable.
add_executable( model Test/main.cpp )

# Link library files to the executable files
target_link_libraries( model modellib )

# ----------------------------------------------------------------------
