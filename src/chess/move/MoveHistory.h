//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_MOVEHISTORY_H
#define CCHESS_MOVEHISTORY_H
#include <optional>
#include <vector>

#include "../board/Board.h"

class MoveHistory {
    std::vector<Move> history;

    public:
    MoveHistory() = default;
    [[nodiscard]] std::optional<Move> get_last_move() const;
    std::vector<Move> get_history() const;
    void push_move(const Move& move);
    Move& peek_last();
    void remove_last();
    bool piece_has_moved (const Piece* piece) const;
};


#endif //CCHESS_MOVEHISTORY_H