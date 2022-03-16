cmake_minimum_required(VERSION 3.17)
project(Clusterbot CXX)

set(CMAKE_CXX_STANDARD 14)


file(GLOB includes "include/**/*.hpp")
file(GLOB extra_includes "include/**/*.hpp")
file(GLOB srcs "srcs/*.cpp")
file(GLOB extra_srcs "srcs/**/*.cpp")

add_executable(clusterbot ${includes} ${extra_includes} ${srcs} ${extra_srcs})
include_directories(include include/MCTS)
