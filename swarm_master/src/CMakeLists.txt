cmake_minimum_required(VERSION 2.8.3)
project(swarm_coordinator)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(swarm_coord_lib_source
	Movement.cpp
	Movement.h
	Node.cpp
	Node.h
	Parse.cpp
	Parse.h
	Read.cpp
	Read.h
	Threading.cpp
	Threading.h
	Write.cpp
	Write.h
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(swarm_coordinator Main.cpp)

add_library(swarm_coordinator_library ${swarm_coord_lib_source})

target_link_libraries(swarm_coordinator swarm_coordinator_library ${catkin_LIBRARIES})

