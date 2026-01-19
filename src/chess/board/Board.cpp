//
// Created by ronzani on 1/17/26.
//

#include "Board.h"

#include "../pieces/Bishop.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"
#include "../pieces/Pawn.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"

void Board::resetBoard() {
    for (auto & i : grid) {
        for (auto & j : i) {
            delete j;
            j = nullptr;
        }
    }
    for (int j = 0; j < 8; j++) {
        grid[1][j] = new Pawn(PieceColor::white);
        grid[6][j] = new Pawn(PieceColor::black);
    }
    grid[0][0] = new Rook(PieceColor::white);
    grid[0][1] = new Knight(PieceColor::white);
    grid[0][2] = new Bishop(PieceColor::white);
    grid[0][3] = new Queen(PieceColor::white);
    grid[0][4] = new King(PieceColor::white);
    grid[0][5] = new Bishop(PieceColor::white);
    grid[0][6] = new Knight(PieceColor::white);
    grid[0][7] = new Rook(PieceColor::white);

    grid[7][0] = new Rook(PieceColor::black);
    grid[7][1] = new Knight(PieceColor::black);
    grid[7][2] = new Bishop(PieceColor::black);
    grid[7][3] = new Queen(PieceColor::black);
    grid[7][4] = new King(PieceColor::black);
    grid[7][5] = new Bishop(PieceColor::black);
    grid[7][6] = new Knight(PieceColor::black);
    grid[7][7] = new Rook(PieceColor::black);
}

Board::Board() : grid{} {
    resetBoard();
}

Piece* Board::atPosition(const Position position) const {
    return grid[position.x][position.y];
}
