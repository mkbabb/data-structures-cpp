project(data_structures)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_COMPILER "clang++")

add_compile_options(-fcoroutines-ts -stdlib=libc++ -std=c++2a -ggdb3)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

# file(GLOB_RECURSE tmp
#     "src/data_structures/utils/*.hpp"
# )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} src/data_structures/utils/pyrange.hpp test/data_structures/tree/tmp.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})




