cmake_minimum_required(VERSION 3.19)
project(OperacoesGrafos)

set(CMAKE_CXX_STANDARD 14)

include_directories(Grafos)

add_executable(OperacoesGrafos
        Grafos/Aresta.cpp
        Grafos/Aresta.h
        Grafos/Grafo.cpp
        Grafos/Grafo.h
        Grafos/main.cpp
        Grafos/Hungaro.cpp
        Grafos/Hungaro.h)
