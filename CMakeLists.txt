cmake_minimum_required(VERSION 4.3)
project(MercadoEnviosAzul)

set(CMAKE_CXX_STANDARD 20)

add_executable(MercadoEnviosAzul main.cpp
        GrupoA/ListaPendientes.cpp
        GrupoA/ListaPendientes.hpp
        GrupoA/NodoPendiente.cpp
        GrupoA/NodoPendiente.hpp
        GrupoA/Estados.hpp
        GrupoB/Movimiento.cpp
        GrupoB/Movimiento.hpp
        GrupoB/NodoMovimiento.cpp
        GrupoB/NodoMovimiento.hpp
        GrupoB/HistorialDeMovimientos.cpp
        GrupoB/HistorialDeMovimientos.hpp)
