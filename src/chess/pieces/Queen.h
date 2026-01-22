//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_QUEEN_H
#define CCHESS_QUEEN_H
#include "Piece.h"


class Queen : public Piece {
public:
    explicit Queen(const PieceColor color) : Piece(PieceKind::queen, color) {}

    std::vector<Position> generateMoves(Position pos, Board& board) override;
};


#endif //CCHESS_QUEEN_H