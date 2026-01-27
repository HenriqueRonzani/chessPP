//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_BISHOP_H
#define CCHESS_BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
public:
    explicit Bishop(const PieceColor color) : Piece(PieceKind::Bishop, color) {}

    [[nodiscard]] std::vector<Position> generateMoves(Position pos, const Board& board) const override;
};


#endif //CCHESS_BISHOP_H