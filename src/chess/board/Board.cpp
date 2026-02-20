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
#include "../move/Interpreter.h"

void Board::resetBoard() {
    for (auto & i : grid) {
        for (auto & j : i) {
            delete j;
            j = nullptr;
        }
    }
    for (int j = 0; j < 8; j++) {
        grid[1][j] = new Pawn(PieceColor::White);
        grid[6][j] = new Pawn(PieceColor::Black);
    }
    grid[0][0] = new Rook(PieceColor::White);
    grid[0][1] = new Knight(PieceColor::White);
    grid[0][2] = new Bishop(PieceColor::White);
    grid[0][3] = new Queen(PieceColor::White);
    grid[0][4] = new King(PieceColor::White);
    grid[0][5] = new Bishop(PieceColor::White);
    grid[0][6] = new Knight(PieceColor::White);
    grid[0][7] = new Rook(PieceColor::White);

    grid[7][0] = new Rook(PieceColor::Black);
    grid[7][1] = new Knight(PieceColor::Black);
    grid[7][2] = new Bishop(PieceColor::Black);
    grid[7][3] = new Queen(PieceColor::Black);
    grid[7][4] = new King(PieceColor::Black);
    grid[7][5] = new Bishop(PieceColor::Black);
    grid[7][6] = new Knight(PieceColor::Black);
    grid[7][7] = new Rook(PieceColor::Black);
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

void Board::movePiece(const Position from, const Position to) {
    grid[to.y][to.x] = grid[from.y][from.x];
    grid[from.y][from.x] = nullptr;
}

void Board::handleCastle(const Move &move) {
    const int rank = move.movedPiece->color == PieceColor::White ? 0 : 7;
    const int rookFile = move.moveText == "O-O" ? 7 : 0;
    const Position rookFrom = {rookFile, rank};
    const int destinyFile = (move.from.x + move.to.x)/2;
    const Position rookTo = {destinyFile, rank};
    movePiece(rookFrom, rookTo);
}

void Board::handleMove(const std::string& moveString) {
    const Move move = Interpreter::parse(moveString, *this);

    movePiece(move.from, move.to);

    if (move.isEnPassant) {
        grid[move.from.y][move.to.x] = nullptr;
    }

    if (move.isCastling) {
        handleCastle(move);
    }

    if (move.promotionType != PieceKind::None) {
        Piece* promoted = Piece::create(move.promotionType, move.movedPiece->color);
        grid[move.to.y][move.to.x] = promoted;
    }

    history.pushMove(move);
}
