cmake_minimum_required(VERSION 2.8.3)
project(swarm_coordinator)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(swarm_coord_lib_source
	Calculation.cpp
	Calculation.h
	Hardware.cpp
	Hardware.h
	mmapGpio.cpp
	mmapGpio.h
	Node.cpp
	Node.h
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(swarm_coordinator Main.cpp)

add_library(swarm_coordinator_library ${swarm_coord_lib_source})

target_link_libraries(swarm_coordinator swarm_coordinator_library ${catkin_LIBRARIES})

