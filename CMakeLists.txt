cmake_minimum_required(VERSION 3.23)
project(DA_PROJECT1)

set(CMAKE_CXX_STANDARD 11)

add_executable(DA_PROJECT1
        main.cpp
        VertexEdge.h
        VertexEdge.cpp
        Graph.h
        Graph.cpp
        Data.h
        Data.cpp
        Station.h
        Station.cpp)
