cmake_minimum_required (VERSION 2.6)
project (TeoCCLTest)
# The version number.
set (TeoCCLTest_VERSION_MAJOR 1)
set (TeoCCLTest_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/TeoCCLTestConfig.h.in"
#  "${PROJECT_BINARY_DIR}/TeoCCLTestConfig.h"
#  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR} ${PROJECT_BINARY_DIR}/../../../../include/libteoccl/")

# add the executable
add_executable(TeoCCLTest main_t.c)