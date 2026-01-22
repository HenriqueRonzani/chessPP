//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_BISHOP_H
#define CCHESS_BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
public:
    explicit Bishop(const PieceColor color) : Piece(PieceKind::bishop, color) {}

    std::vector<Position> generateMoves(Position pos, Board& board) override;
};


#endif //CCHESS_BISHOP_H