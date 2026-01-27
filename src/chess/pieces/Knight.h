//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_KNIGHT_H
#define CCHESS_KNIGHT_H
#include "Piece.h"


class Knight : public Piece {
public:
    explicit Knight(const PieceColor color) : Piece(PieceKind::Knight, color) {}

    [[nodiscard]] std::vector<Position> generateMoves(Position pos, const Board& board) const override;
};


#endif //CCHESS_KNIGHT_H