
project (test_eigen CXX C)
cmake_minimum_required(VERSION 2.8)
# set the version number

set (PROJECT_VERSION_MAJOR 1)
set (PROJECT_VERSION_MINOR 0)
set (PROJECT_PATCH_VERSION 0)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(PythonLibs)
include_directories(eigen ${PYTHON_INCLUDE_PATH} ${NUMPY_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-DMS_WIN64 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (NOT CMAKE_SHARED_MODULE_CREATE_CXX_FLAGS)
   set(CMAKE_SHARED_MODULE_CREATE_CXX_FLAGS ${CMAKE_SHARED_MODULE_CREATE_C_FLAGS})
endif(NOT CMAKE_SHARED_MODULE_CREATE_CXX_FLAGS)

set_source_files_properties(RBFinterp.i PROPERTIES CPLUSPLUS ON)
swig_add_module(RBFinterp python RBFinterp.i RBFinterp.cpp)
swig_link_libraries(RBFinterp ${PYTHON_LIBRARIES})