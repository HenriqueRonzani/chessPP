//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_QUEEN_H
#define CCHESS_QUEEN_H
#include "Piece.h"


class Queen : public Piece {
public:
    explicit Queen(const PieceColor color) : Piece(PieceKind::Queen, color) {}

    [[nodiscard]] std::vector<Position> generateMoves(Position pos, const Board& board) const override;
};


#endif //CCHESS_QUEEN_H