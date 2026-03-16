//
// Created by ronzani on 1/18/26.
//

#include "MoveHistory.h"

#include <algorithm>

#include "../pieces/Piece.h"

std::optional<Move> MoveHistory::get_last_move() const {
    if (history.empty()) return std::nullopt;
    return history.back();
}

void MoveHistory::push_move(const Move& move) {
    history.push_back(move);
}

bool MoveHistory::piece_has_moved(const Piece *piece) const {
    return std::ranges::any_of(history, [&](const Move& move) {
        return move.moved_piece == piece;
    });
}
