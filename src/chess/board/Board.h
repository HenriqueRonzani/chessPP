//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_BOARD_H
#define CCHESS_BOARD_H
#include "Position.h"
#include <string>
#include "../pieces/Piece.h"

class Piece;

class Board {
    Piece* grid[8][8];
public:
    MoveHistory history;
    void resetBoard();
    Board();
    [[nodiscard]] Piece* atPosition(Position position) const;
    [[nodiscard]] std::string toString() const;
    [[nodiscard]] Position findMoveablePiece (Position target, PieceKind kind, PieceColor color, int pieceColumn = -1, int pieceRow = -1) const;
};


#endif //CCHESS_BOARD_H