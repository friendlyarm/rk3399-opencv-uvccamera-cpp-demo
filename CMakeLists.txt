# cmake needs this line 
cmake_minimum_required(VERSION 2.8) 

# Enable C++11 
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED TRUE) 

# Define project name 
project(opencamera) 

# Find OpenCV, you may need to set OpenCV_DIR variable 
# to the absolute path to the directory containing OpenCVConfig.cmake file 
# via the command line or GUI 
find_package(OpenCV 4.1.0 REQUIRED COMPONENTS core highgui calib3d) 
include_directories( ${OpenCV_INCLUDE_DIRS} ) 

# Declare the executable target built from your sources 
add_executable(opencamera opencamera.cpp) 

# Link your application with OpenCV libraries 
target_link_libraries(opencamera ${OpenCV_LIBS})

