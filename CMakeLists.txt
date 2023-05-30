cmake_minimum_required(VERSION 3.20.0)

project(SimpleConfigurationSample)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
	add_definitions( -DCMAKE_APPLE_SILICON_PROCESSOR=arm64 )
endif(APPLE)

add_executable(${PROJECT_NAME} 
	main.cpp
	)