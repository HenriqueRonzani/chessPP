//
// Created by ronzani on 1/18/26.
//

#include "Knight.h"

std::vector<Position> Knight::generate_pseudo_legal_moves(const Position pos, const Board &board) const {
    static const std::vector<Position> move_directions = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2},
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };
    return generate_sliding_moves(pos, board, move_directions, 1);
}
