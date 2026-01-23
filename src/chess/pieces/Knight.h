//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_KNIGHT_H
#define CCHESS_KNIGHT_H
#include "Piece.h"


class Knight : public Piece {
public:
    explicit Knight(const PieceColor color) : Piece(PieceKind::knight, color) {}

    std::vector<Position> generateMoves(Position pos, Board& boardn) override;
};


#endif //CCHESS_KNIGHT_H