project(data_structures)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_COMPILER "g++-10")

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  message(STATUS "Build type not specified: Use Release by default")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(TESTS_NAME test)

add_executable(${TESTS_NAME} test/data_structures/tree/tmp.cpp)
target_link_libraries(${TESTS_NAME} ${CONAN_LIBS})




