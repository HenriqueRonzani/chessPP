//
// Created by ronzani on 1/18/26.
//

#include "King.h"

#include <algorithm>

std::vector<Position> King::generateMoves(const Position pos, const Board &board) const {
    const std::vector<Position> diagonalDirections = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    const std::vector<Position> horizontalDirections = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    std::vector<Position> moves = generateSlidingMoves(pos, board, horizontalDirections, 1);
    std::vector<Position> diagonalMoves = generateSlidingMoves(pos, board, diagonalDirections, 1);

    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());

    if (!board.history.pieceHasMoved(this)) {
        const Piece* hRook = board.atPosition({pos.x + 3, pos.y});
        if (hRook && !board.history.pieceHasMoved(hRook)) {
            if (!board.atPosition({pos.x + 1, pos.y}) &&
                !board.atPosition({pos.x + 2, pos.y})
                )
                moves.push_back({pos.x + 2, pos.y});
        }

        const Piece* aRook = board.atPosition({pos.x - 4, pos.y});
        if (aRook && !board.history.pieceHasMoved(aRook)) {
            if (!board.atPosition({pos.x - 1, pos.y}) &&
                !board.atPosition({pos.x - 2, pos.y}) &&
                !board.atPosition({pos.x - 3, pos.y})
                )
                moves.push_back({pos.x - 2, pos.y});
        }
    }
    return moves;
}
