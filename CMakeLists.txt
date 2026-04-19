cmake_minimum_required(VERSION 4.1)
project(cchess)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
message(STATUS "Downloading Raylib...")
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
)
FetchContent_MakeAvailable(raylib)

add_library(cchess_engine
        src/chess/pieces/Piece.h
        src/chess/board/Board.cpp
        src/chess/board/Board.h
        src/chess/pieces/Pawn.cpp
        src/chess/pieces/Pawn.h
        src/chess/pieces/King.cpp
        src/chess/pieces/King.h
        src/chess/pieces/Queen.cpp
        src/chess/pieces/Queen.h
        src/chess/pieces/Knight.cpp
        src/chess/pieces/Knight.h
        src/chess/pieces/Rook.cpp
        src/chess/pieces/Rook.h
        src/chess/pieces/Bishop.cpp
        src/chess/pieces/Bishop.h
        src/chess/move/MoveHistory.cpp
        src/chess/move/MoveHistory.h
        src/chess/pieces/Piece.cpp
        src/chess/move/Interpreter.cpp
        src/chess/move/Interpreter.h
        src/chess/move/Token.cpp
        src/chess/move/Token.h
        src/chess/Engine.h
        src/chess/helpers/BoardHelper.cpp
        src/chess/helpers/BoardHelper.h
        src/chess/ChessTypes.h
        src/chess/helpers/PieceHelper.h
)

target_include_directories(cchess_engine PUBLIC src)

# ===========================
#            CLI
# ===========================

add_executable(cchess_cli src/cli/main_cli.cpp)
target_link_libraries(cchess_cli PRIVATE cchess_engine)

# ===========================
#            GUI
# ===========================

add_executable(cchess_gui
        src/gui/main_gui.cpp
        src/gui/render/Screen.cpp
        src/gui/render/Screen.h)
target_link_libraries(cchess_gui PRIVATE cchess_engine raylib)