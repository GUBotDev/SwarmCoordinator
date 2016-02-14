cmake_minimum_required(VERSION 2.8.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(swarm_coord_lib_source
	Calculation.cpp
	Calculation.h
	ControllerNode.cpp
	ControllerNode.h
	FollowerNode.cpp
	FollowerNode.h
	Movement.cpp
	Movement.h
)

add_library(swarm_coordinator_library ${swarm_coord_lib_source})

add_executable(swarm_coordinator Main.cpp)

target_link_libraries(swarm_coordinator swarm_coordinator_library)

