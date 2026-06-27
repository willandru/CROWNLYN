cmake_minimum_required(VERSION 3.20)

project(CROWNLYN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================================
# DEPENDENCIAS EXTERNAS
# ======================================================

add_subdirectory(externals/glfw-3.4)

add_library(glad
    externals/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    externals/glad/include
)

# ======================================================
# FUENTES COMPARTIDAS (LÓGICA)
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
# FUENTES GRÁFICAS
# ======================================================

set(CROWNLYN_GRAPHICS

    src/Graphics/Window.cpp
    src/Graphics/Input.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/Shader.cpp

    src/UI/Button.cpp

    src/Screens/MainMenuScreen.cpp
    src/Screens/OneScreen.cpp
    src/Screens/OneVsAIScreen.cpp
    src/Screens/MatchScreen.cpp
    src/Screens/ScreenManager.cpp
    src/Screens/SpecialMovesScreen.cpp
    src/Screens/HistoryMovesScreen.cpp
    src/Screens/HistoryEndingsScreen.cpp
    src/Screens/RewardsMainMenu.cpp

    src/Game/ImagenManager.cpp
    src/Screens/DrawTableroEngine.cpp
    src/Screens/DrawGameEngine.cpp

    src/Arbol/Tablero.cpp

    src/Fichas/Ficha.cpp
    src/Fichas/Torre.cpp
    src/Game/DrawFichaEngine.cpp
    src/Game/TableroBuilder.cpp

)

# ======================================================
# PROGRAMA PRINCIPAL (LÓGICA)
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
    src/Game
)

# ======================================================
# PROGRAMA GRÁFICO
# ======================================================

add_executable(
    RENDER_WINDOW

    mainGrafics.cpp

    ${CROWNLYN_GRAPHICS}
)

target_include_directories(
    RENDER_WINDOW
    PRIVATE

    src
    src/Graphics
    src/Screens
    src/UI
    src/Game
    src/Arbol
    src/Fichas

    externals/glad/include
    externals/glfw-3.4/include
    externals/glm
    externals/stb

    assets
)

target_link_libraries(
    RENDER_WINDOW
    PRIVATE

    glad
    glfw
)

if(WIN32)
    target_link_libraries(
        RENDER_WINDOW
        PRIVATE
        opengl32
    )
endif()

add_custom_command(
    TARGET RENDER_WINDOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/Graphics/Shaders/basic.vert
        $<TARGET_FILE_DIR:RENDER_WINDOW>/basic.vert
)

add_custom_command(
    TARGET RENDER_WINDOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/Graphics/Shaders/basic.frag
        $<TARGET_FILE_DIR:RENDER_WINDOW>/basic.frag
)

add_custom_command(
    TARGET RENDER_WINDOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/Graphics/Shaders/texture.vert
        $<TARGET_FILE_DIR:RENDER_WINDOW>/texture.vert
)

add_custom_command(
    TARGET RENDER_WINDOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/Graphics/Shaders/texture.frag
        $<TARGET_FILE_DIR:RENDER_WINDOW>/texture.frag
)



add_custom_command(
    TARGET RENDER_WINDOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/Assets/image.png
        $<TARGET_FILE_DIR:RENDER_WINDOW>/image.png
)

add_custom_command(
    TARGET RENDER_WINDOW POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/Assets/torre.png
        $<TARGET_FILE_DIR:RENDER_WINDOW>/torre.png
)

set_target_properties(
    RENDER_WINDOW
    PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# ======================================================
# TESTS
# ======================================================

add_executable(
    CROWNLYN_TESTS

    TestsMain.cpp

    src/Test/TestSuite.cpp
    src/Test/TestStates.cpp
    src/Test/TestGameAnalyzer.cpp
    src/Test/TestDecisionTreeEngine.cpp

    ${CROWNLYN_CORE}
)

target_include_directories(
    CROWNLYN_TESTS
    PRIVATE

    src
    src/Arbol
    src/Fichas
    src/Test
    src/Game
)