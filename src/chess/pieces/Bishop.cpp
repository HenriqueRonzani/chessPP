//
// Created by ronzani on 1/18/26.
//

#include "Bishop.h"

std::vector<Position> Bishop::generateMoves(const Position pos, const Board &board) const {
    const std::vector<Position> moveDirections = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    return generateSlidingMoves(pos, board, moveDirections);
}
