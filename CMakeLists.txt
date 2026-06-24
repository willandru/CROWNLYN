cmake_minimum_required(VERSION 3.16)

project(CROWNLYN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp

    src/Arbol/Arbol.cpp
    src/Arbol/Nodo.cpp
    src/Arbol/Tablero.cpp
    src/Arbol/Turno.cpp
    src/Arbol/DecisionTreeEngine.cpp
    src/Arbol/GameAnalyzer.cpp
    src/Arbol/StateEvaluator.cpp

    src/Fichas/Ficha.cpp
    src/Fichas/Peon.cpp
    src/Fichas/Torre.cpp
    src/Fichas/Alfil.cpp
    src/Fichas/Caballo.cpp
    src/Fichas/Dama.cpp
    src/Fichas/Rey.cpp
)

add_executable(CROWNLYN ${SOURCES})

target_include_directories(CROWNLYN PRIVATE
    src
    src/Arbol
    src/Fichas
)