cmake_minimum_required(VERSION 2.8)
project(OPENNI2)

#find_package(OpenNI2 REQUIRED)
#find_package(OpenNI2 REQUIRED)
MESSAGE(STATUS "USING BUNDLED FindOpenNI.cmake ...")
FIND_PATH(OPENNI_INCLUDE_DIR NAMES XnCppWrapper.h
    PATHS
    /usr/include/ni 
  )
 
FIND_LIBRARY(OPENNI_LIBRARY_DIR NAMES OpenNI
     PATHS
     /usr/lib
   )


include_directories($ENV{OPENNI2_INCLUDE})
link_directories($ENV{OPENNI2_REDIST})
message($ENV{OPENNI2_INCLUDE})
message($ENV{OPENNI2_REDIST})
find_package(OpenCV REQUIRED)

add_executable(rgb_img src/main.cpp)
add_executable(depth_img src/depth.cpp)

target_link_libraries(rgb_img ${OpenCV_LIBS} libOpenNI2.so )
target_link_libraries(depth_img ${OpenCV_LIBS} libOpenNI2.so )

