cmake_minimum_required(VERSION 3.17)
project(Clusterbot C)

set(CMAKE_C_STANDARD 11)


file(GLOB includes "include/*.h")
file(GLOB srcs "srcs/*.c")

add_executable(clusterbot ${includes} ${srcs})
include_directories(include)
