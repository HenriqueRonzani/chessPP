//
// Created by ronzani on 1/18/26.
//

#include "MoveHistory.h"

#include <algorithm>

std::optional<Move> MoveHistory::get_last_move() const {
    if (history.empty()) return std::nullopt;
    return history.back();
}

std::vector<Move> MoveHistory::get_history() const {
    return history;
}

void MoveHistory::push_move(const Move& move) {
    history.push_back(move);
}

void MoveHistory::remove_last() {
    history.pop_back();
}

Move& MoveHistory::peek_last() {
    return history.back();
}

bool MoveHistory::piece_has_moved(const Piece *piece) const {
    return std::ranges::any_of(history, [&](const Move& move) {
        return move.moved_piece == piece;
    });
}
