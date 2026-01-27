//
// Created by ronzani on 1/18/26.
//

#include "Knight.h"

std::vector<Position> Knight::generateMoves(const Position pos, const Board &board) const {
    static const std::vector<Position> moveDirections = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2},
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };
    return generateSlidingMoves(pos, board, moveDirections, 1);
}
