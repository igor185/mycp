cmake_minimum_required(VERSION 3.10.2)
project(mycp
        VERSION 1.0.0
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Options
option(WARNINGS_AS_ERRORS   "Treat compiler warnings as errors."    OFF)
option(ENABLE_PVS_STUDIO    "Use PVS-Studio static code analyzer."  OFF)
option(ENABLE_SANITIZERS    "Use sanitizers to detect errors."      OFF)
option(ENABLE_CONAN         "Use Conan as a package manager."       OFF)

# Include default CMake configuration
include(cmake/defaults.cmake)

# Project source compilation
include_directories(inc)
add_library(IO STATIC src/IO.cpp inc/IO.h)
add_library(util STATIC src/util.cpp inc/util.h)
add_executable(mycp src/main.cpp)
target_link_libraries(mycp IO util)

# Add external packages
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.65.1 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(mycp Boost::program_options)

# PVS-Studio configuration
if (ENABLE_PVS_STUDIO)
    # CMake targets to which apply PVS-Studio
    pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
                          OUTPUT FORMAT errorfile
                          ANALYZE arithmetic add
                          LOG target.err)
endif ()

# Sanitizers configuration
if (ENABLE_SANITIZERS)
    # CMake targets to which apply sanitizers
    add_sanitizers(IO util add)
endif ()
