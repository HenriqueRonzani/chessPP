//
// Created by ronzani on 1/18/26.
//

#include "Rook.h"

std::vector<Position> Rook::generate_pseudo_legal_moves(const Position pos, const Board &board) const {
    static const std::vector<Position> move_directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    return generate_sliding_moves(pos, board, move_directions);
}
