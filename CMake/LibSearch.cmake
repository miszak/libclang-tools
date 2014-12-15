# Libraries search

#INCLUDE(FindLibClang.cmake)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake)

MESSAGE(STATUS "${PROJECT_NAME}: Configuring libraries")

# libclang
#FIND_PACKAGE(LibClang REQUIRED)
SET(LibClang_VERSION 3.5)
SET(LibClang_INCLUDE_DIRS ${PATH_TO_LLVM_ROOT}/include)
SET(LibClang_LIBRARIES ${PATH_TO_LLVM_ROOT}/lib)

# Status messages
MESSAGE(STATUS " ${PROJECT_NAME}: LibClang_VERSION=${LibClang_VERSION}")
MESSAGE(STATUS " ${PROJECT_NAME}: LibClang_INCLUDE_DIRS=${LibClang_INCLUDE_DIRS}")
MESSAGE(STATUS " ${PROJECT_NAME}: LibClang_LIBRARIES=${LibClang_LIBRARIES}")

