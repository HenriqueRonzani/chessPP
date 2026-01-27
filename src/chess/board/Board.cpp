//
// Created by ronzani on 1/17/26.
//

#include "Board.h"

#include <stdexcept>

#include "../pieces/Bishop.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"
#include "../pieces/Pawn.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"
#include "./Position.h"

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
    if (position.isValid())
        return grid[position.y][position.x];
    return nullptr;
}

std::string Board::toString() const {
    std::string boardString;
    for (int i = 7; i >= 0; i--) {
        boardString += std::to_string(i) + " ";
        for (int j = 0; j < 8; j++) {
            if (const Piece* piece = grid[i][j]; piece != nullptr)
                boardString += piece->toChar();
            else
                boardString += "-";
            boardString += " ";
        }
        boardString += "\n";
    }
    return boardString;
}

Position Board::findMoveablePiece(
    const Position target,
    const PieceKind kind,
    const PieceColor color,
    const int pieceColumn,
    const int pieceRow
    ) const {
    std::vector<Position> moveablePiecesPositions;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Piece* piece = grid[j][i];
            if (!piece || piece->kind != kind || piece->color != color) continue;

            if (pieceColumn != -1 && pieceColumn != i) continue;
            if (pieceRow != -1 && pieceRow != j) continue;

            if (piece->isValidMove({i, j}, target, *this)) {
                moveablePiecesPositions.emplace_back(i, j);
            }
        }
    }

    if (moveablePiecesPositions.empty())
        throw std::invalid_argument("No pieces are able to do this move");

    if (moveablePiecesPositions.size() > 1)
        throw std::invalid_argument("Multiple pieces are able to do this move");

    return moveablePiecesPositions[0];
}
