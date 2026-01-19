//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_PIECE_H
#define CCHESS_PIECE_H

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
    PieceKind kind;
    PieceColor color;

    public:
    Piece(PieceKind kind, PieceColor color);
    virtual ~Piece() = default;

    virtual void move(int x1, int y1, int x2, int y2, Piece* board[8][8]);
};


#endif //CCHESS_PIECE_H