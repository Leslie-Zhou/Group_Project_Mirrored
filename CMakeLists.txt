# THIS CMAKELISTS FILE IS ONLY FOR TESTING AND ONLY TO BE USED BY TRAVIS
# To compile the Model Viewer using cmake, use the CMAKELISTS file under ModelViewer Directory

# Travis will auto-run these tests, so this cmakelists is not intended to be used by a user.

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# If travis
if( UNIX )
include(CTest)

# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Include the header/source and test folders of the model library.
include_directories (ModelViewer/Model_Library/Test)
include_directories (ModelViewer/Model_Library/Code)

# Add Model Library
add_library( modellib ModelViewer/Model_Library/Code/model.cpp ModelViewer/Model_Library/Code/Material.cpp 
		      ModelViewer/Model_Library/Code/Cell.cpp ModelViewer/Model_Library/Code/vectorClass.cpp 
               	      ModelViewer/Model_Library/Code/model.h ModelViewer/Model_Library/Code/Material.h 
		      ModelViewer/Model_Library/Code/Cell.h ModelViewer/Model_Library/Code/vectorClass.h )

# Testing

# Send a copy of the provided sample mod files into the build folder 
# so that model test could import them.
file( GLOB MOD_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewer/Model_Library/Example_Model_Files/*.mod )
file( COPY ${MOD_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

# add model and vector test source files
add_executable ( model_test ModelViewer/Model_Library/Test/model_test.cpp )
add_executable ( vector_test ModelViewer/Model_Library/Test/vector_test.cpp )

# link the model library with the test
target_link_libraries( model_test modellib )
target_link_libraries( vector_test modellib )

# add the tests
# Use CTEST (windows) or make test (Linux) to run the tests manually
add_test( model_test model_test )
add_test( vector_test vector_test )

else()
message ( FATAL_ERROR "This CMakeLists is intended to only be used by Travis for testing. To compile the Model Viewer Program, use the CMAKELISTS file under ModelViewer Directory." )
endif( UNIX ) 