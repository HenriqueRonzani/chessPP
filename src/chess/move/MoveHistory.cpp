//
// Created by ronzani on 1/18/26.
//

#include "MoveHistory.h"

#include <algorithm>

#include "../pieces/Piece.h"

std::optional<Move> MoveHistory::getLastMove() const {
    if (history.empty()) return std::nullopt;
    return history.back();
}

PieceColor MoveHistory::getNextMoveColor() const {
    const std::optional<Move> lastMove = getLastMove();
    return lastMove
        ? Piece::getOpposingColor(lastMove->movedPiece->color)
        : PieceColor::White;
}

void MoveHistory::pushMove(const Move& move) {
    history.push_back(move);
}

bool MoveHistory::pieceHasMoved(const Piece *piece) const {
    return std::ranges::any_of(history, [&](const Move& move) {
        return move.movedPiece == piece;
    });
}
