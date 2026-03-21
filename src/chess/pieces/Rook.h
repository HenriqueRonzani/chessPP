//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_ROOK_H
#define CCHESS_ROOK_H
#include "Piece.h"

class Rook : public Piece {
public:
    explicit Rook(const PieceColor color) : Piece(PieceKind::Rook, color) {}

    [[nodiscard]] std::vector<Position> generate_pseudo_legal_moves(Position pos, const Board& board) const override;
};


#endif //CCHESS_ROOK_H