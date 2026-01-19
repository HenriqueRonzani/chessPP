cmake_minimum_required(VERSION 4.1)
project(cchess)

set(CMAKE_CXX_STANDARD 20)

add_executable(cchess main.cpp
        src/chess/pieces/Piece.cpp
        src/chess/pieces/Piece.h
        src/chess/board/Board.cpp
        src/chess/board/Board.h
        src/chess/pieces/Pawn.cpp
        src/chess/pieces/Pawn.h
        src/chess/pieces/King.cpp
        src/chess/pieces/King.h
        src/chess/pieces/King.h
        src/chess/pieces/King.h
        src/chess/pieces/Queen.cpp
        src/chess/pieces/Queen.h
        src/chess/pieces/Knight.cpp
        src/chess/pieces/Knight.h
        src/chess/pieces/Rook.cpp
        src/chess/pieces/Rook.h
        src/chess/pieces/Bishop.cpp
        src/chess/pieces/Bishop.h
)
