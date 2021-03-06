
cmake_minimum_required (VERSION 3.10)

project (ArgosCustomController)

set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(PkgConfig)
pkg_check_modules(ARGOS REQUIRED argos3_simulator)
set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)

# Check whether all the necessary libs have been installed to compile the
# code that depends on Qt and OpenGL
include(ARGoSCheckQTOpenGL)

# Look for the (optional) galib library
find_package(GALIB)
if(GALIB_FOUND)
  include_directories(${GALIB_INCLUDE_DIRS})
endif(GALIB_FOUND)

# Find Lua
find_package(Lua53 REQUIRED)

# Set ARGoS include dir
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

# Set ARGoS link dir
link_directories(${ARGOS_LIBRARY_DIRS})

add_subdirectory(controllers)

add_subdirectory(loop_function)

add_executable(GeneticEvolution genetic_evolution.cpp)
add_executable(TestController test_controller.cpp)
add_executable(Race race.cpp)


target_link_libraries(TestController
  ${GALIB_LIBRARIES}
  genetic_controller
  single_robot_loop_function
  argos3core_simulator)


target_link_libraries(GeneticEvolution
  ${GALIB_LIBRARIES}
  genetic_controller
  single_robot_loop_function
  argos3core_simulator)


target_link_libraries(Race
  ${GALIB_LIBRARIES}
  genetic_controller
  race_loop_function
  argos3core_simulator)


target_include_directories(GeneticEvolution PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/controllers"
                          "${PROJECT_SOURCE_DIR}/loop_function"
                          )

target_include_directories(TestController PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/controllers"
                          "${PROJECT_SOURCE_DIR}/loop_function"
                          )