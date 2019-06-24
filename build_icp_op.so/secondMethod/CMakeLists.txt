cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(icp_op)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Add tensorflow framework

execute_process(COMMAND python -c "import tensorflow as tf; print(tf.sysconfig.get_lib())" OUTPUT_VARIABLE TF_LIB_DIR)
execute_process(COMMAND python -c "import tensorflow as tf; print(tf.sysconfig.get_include())" OUTPUT_VARIABLE TF_INC_DIR)
string(REGEX REPLACE "\n$" "" TF_INC_DIR  "${TF_INC_DIR}")
string(REGEX REPLACE "\n$" "" TF_LIB_DIR  "${TF_LIB_DIR}")

include_directories(SYSTEM ${TF_INC_DIR})

find_library(
  TF_FRAMEWORK
  NAMES tensorflow_framework
  PATHS ${TF_LIB_DIR}
)

message(STATUS "tensorflow_framework library found: in ${TF_FRAMEWORK}")


include_directories("/usr/local/include/eigen3")

find_package(PCL 1.8 REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(/home/anotherday/anaconda3/envs/struct2depth/lib/python2.7/site-packages/tensorflow/include)
link_directories(/home/anotherday/anaconda3/envs/struct2depth/lib/python2.7/site-packages/tensorflow/)

#include_directories("${EIGEN3_INCLUDE_DIR}")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

add_library(icp_op SHARED icp_op_kernel.cc)
target_link_libraries(icp_op ${PCL_LIBRARIES}  ${TF_FRAMEWORK} )
