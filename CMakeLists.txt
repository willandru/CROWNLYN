cmake_minimum_required(VERSION 3.16)

project(CROWNLYN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================
# FUENTES COMPARTIDAS
# ======================================================

set(CROWNLYN_CORE

    src/Arbol/Arbol.cpp
    src/Arbol/Nodo.cpp
    src/Arbol/Tablero.cpp
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

# ======================================================
# PROGRAMA PRINCIPAL
# ======================================================

add_executable(
    CROWNLYN

    main.cpp

    ${CROWNLYN_CORE}
)

target_include_directories(
    CROWNLYN
    PRIVATE

    src
    src/Arbol
    src/Fichas
)

# ======================================================
# TESTS
# ======================================================

add_executable(
    CROWNLYN_TESTS

    TestsMain.cpp

    src/Test/TestStates.cpp

    ${CROWNLYN_CORE}
)

target_include_directories(
    CROWNLYN_TESTS
    PRIVATE

    src
    src/Arbol
    src/Fichas
    src/Test
)