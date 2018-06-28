cmake_minimum_required(VERSION 3.1)
project(absl_test)

set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED 14)

# Make the default build type Release
if ( NOT CMAKE_CONFIGURATION_TYPES )
  if ( NOT CMAKE_BUILD_TYPE )
    message ( STATUS "No build type selected, default to Release." )
    set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
      "MinSizeRel" "RelWithDebInfo")
  else ()
    message ( STATUS "Build type is " ${CMAKE_BUILD_TYPE} )
  endif ()
endif()

find_package(Boost)

add_subdirectory(abseil-cpp)

add_executable(absl_test test.cpp)

target_link_libraries(absl_test absl::base absl::synchronization absl::strings Boost::boost)
