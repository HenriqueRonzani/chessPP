//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_ROOK_H
#define CCHESS_ROOK_H
#include "Piece.h"


class Rook : public Piece {
public:
    explicit Rook(const PieceColor color) : Piece(PieceKind::rook, color) {}

    bool isValidMove(Position from, Position to, Board& board) override;
    std::vector<Position> generateMoves(Position pos, Board& board) override;
};


#endif //CCHESS_ROOK_H