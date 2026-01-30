//
// Created by ronzani on 1/18/26.
//

#include "MoveHistory.h"

#include "../pieces/Piece.h"

std::optional<Move> MoveHistory::getLastMove() const {
    if (history.empty()) return std::nullopt;
    return history.back();
}

PieceColor MoveHistory::getNextMoveColor() const {
    const std::optional<Move> lastMove = getLastMove();
    return lastMove
        ? Piece::getOpposingColor(lastMove->movedPiece->color)
        : PieceColor::white;
}

void MoveHistory::pushMove(const Move& move) {
    history.push_back(move);
}
