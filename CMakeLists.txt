CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)

# Get the compiler stuff done (before the project is started)
INCLUDE(CMake/Compiler.cmake)

PROJECT(libclang-tools)

MESSAGE(STATUS "${PROJECT_NAME}:" )
MESSAGE(STATUS "${PROJECT_NAME}: BEGIN" )
MESSAGE(STATUS "${PROJECT_NAME}: Configuring project" )

# Set default build type
# build types:
#  debug - build with debugging code flags (default)
#  release - build for deployment

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "debug" CACHE INTERNAL "Choose the type of build" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

# Set proper compile flags
INCLUDE(CMake/CompilerFlags.cmake)

STRING(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)

MESSAGE(STATUS "${PROJECT_NAME}: Build type: ${CMAKE_BUILD_TYPE}" )

# Output directories
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Download Clang
INCLUDE(CMake/GetClang.cmake)

# Libs
INCLUDE(CMake/LibSearch.cmake)

# Include directories
INCLUDE_DIRECTORIES(${LibClang_INCLUDE_DIRS})

# Link directories
LINK_DIRECTORIES(${LibClang_LIBRARIES})

# Target 'main'
SET(TARGET_main main)
ADD_EXECUTABLE(${TARGET_main} main.cpp)
TARGET_LINK_LIBRARIES(${TARGET_main} clang)

################################################################################

MESSAGE(STATUS "${PROJECT_NAME}: END." )
MESSAGE(STATUS "${PROJECT_NAME}:" )
