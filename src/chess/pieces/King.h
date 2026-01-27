//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_KING_H
#define CCHESS_KING_H
#include "Piece.h"


class King : public Piece {
public:
    explicit King(const PieceColor color) : Piece(PieceKind::King, color) {}

    [[nodiscard]] std::vector<Position> generateMoves(Position pos, const Board& board) const override;
};


#endif //CCHESS_KING_H