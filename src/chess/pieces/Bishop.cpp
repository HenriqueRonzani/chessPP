//
// Created by ronzani on 1/18/26.
//

#include "Bishop.h"

std::vector<Position> Bishop::generate_pseudo_legal_moves(const Position pos, const Board &board) const {
    static const std::vector<Position> move_directions = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    return generate_sliding_moves(pos, board, move_directions);
}
