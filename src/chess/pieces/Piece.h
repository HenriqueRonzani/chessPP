//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_PIECE_H
#define CCHESS_PIECE_H
#include "../board/Board.h"
#include "../move/MoveHistory.h"

enum class PieceKind {
    king,
    queen,
    rook,
    knight,
    bishop,
    pawn
};

enum class PieceColor {
    black,
    white
};

class Piece {
public:
    PieceColor color;
    PieceKind kind;
    Piece(PieceKind kind, PieceColor color);
    virtual ~Piece() = default;

    virtual bool isValidMove(Position from, Position to, Board& board);
    virtual std::vector<Position> generateMoves(Position pos, Board& board);
};


#endif //CCHESS_PIECE_H