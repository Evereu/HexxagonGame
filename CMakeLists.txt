cmake_minimum_required(VERSION 3.25.2)
project(Projekt_start)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.1.1
)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(sfml)

add_executable(Projekt_start main.cpp
        View/Menu.cpp
        View/Menu.h
        View/RenderMap.cpp
        View/RenderMap.h
        View/HexagonField.cpp
        View/HexagonField.h
        View/MenuItem.cpp
        View/MenuItem.h
        Logic/Move.cpp
        Logic/Move.h
        Logic/MapStates.cpp
        Logic/MapStates.h
        Logic/GameState.cpp
        Logic/GameState.h
        Logic/MenuState.cpp
        Logic/MenuState.h
        View/ScoreView.cpp
        View/ScoreView.h
        Logic/SaveScore.cpp
        Logic/SaveScore.h
        Logic/Game.cpp
        Logic/Game.h
)

target_link_libraries(
        Projekt_start
        fmt
        sfml-graphics
        sfml-window
        sfml-system
)
IF (WIN32)
    add_custom_command(TARGET Projekt_start POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Projekt_start> $<TARGET_FILE_DIR:Projekt_start>
            COMMAND_EXPAND_LISTS
    )
ENDIF ()