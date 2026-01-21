//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_PAWN_H
#define CCHESS_PAWN_H
#include "Piece.h"

class Pawn : public Piece {
public:
    explicit Pawn(const PieceColor color) : Piece(PieceKind::pawn, color) {}

    std::vector<Position> generateMoves(Position pos, Board& board) override;
};


#endif //CCHESS_PAWN_H