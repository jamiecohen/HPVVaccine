cmake_minimum_required(VERSION 3.14)
project(HPVVaccine)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES main.cpp woman.h woman.cpp statemachine.cpp statemachine.h outputs.cpp outputs.h inputs.cpp inputs.h iniFile.cpp iniFile.h calibrate.cpp calibrate.h helper.cpp helper.h)

find_package(Boost 1.65.1 COMPONENTS filesystem thread REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(HPVVaccine ${SOURCE_FILES})
    target_link_libraries(HPVVaccine ${Boost_LIBRARIES})
endif()