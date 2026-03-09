//
// Created by ronzani on 1/18/26.
//

#include "King.h"

bool isSquareFreeAndSafe (
    const Position pos,
    const Board & board,
    const PieceColor kingColor) {

    return !board.atPosition(pos) &&
        !board.isSquareAttacked(pos, kingColor);
}

std::vector<Position> King::generateMoves(const Position pos, const Board &board) const {
    static const std::vector<Position> kingDirections = {
        {1, -1}, {-1, 1}, {1, 1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    std::vector<Position> moves = generateSlidingMoves(pos, board, kingDirections, 1);

    const PieceColor kingColor = board.atPosition(pos)->color;

    if (!board.history.pieceHasMoved(this) && !board.isKingAttacked(kingColor)) {

        const Piece* hRook = board.atPosition({pos.x + 3, pos.y});
        if (hRook && !board.history.pieceHasMoved(hRook)) {
            if (isSquareFreeAndSafe({pos.x + 1, pos.y}, board, kingColor) &&
                isSquareFreeAndSafe({pos.x + 2, pos.y}, board, kingColor)
                )
                moves.push_back({pos.x + 2, pos.y});
        }

        const Piece* aRook = board.atPosition({pos.x - 4, pos.y});
        if (aRook && !board.history.pieceHasMoved(aRook)) {
            if (isSquareFreeAndSafe({pos.x - 1, pos.y}, board, kingColor) &&
                isSquareFreeAndSafe({pos.x - 2, pos.y}, board, kingColor) &&
                board.atPosition({pos.x - 3, pos.y}) == nullptr
                )
                moves.push_back({pos.x - 2, pos.y});
        }
    }
    return moves;
}
