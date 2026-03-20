//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_MOVEHISTORY_H
#define CCHESS_MOVEHISTORY_H
#include <optional>
#include <string>
#include <vector>

#include "../board/Board.h"
#include "../board/Position.h"
#include "../pieces/PieceTypes.h"

class Piece;

struct Move {
    std::string move_string;
    const Piece* moved_piece;
    const Piece* captured_piece = nullptr;
    Position moved_from_position;
    Position moved_to_position;

    bool is_castle = false;
    bool is_en_passant = false;
    PieceKind promotion_type = PieceKind::None;
    GameState previous_state;
};

class MoveHistory {
    std::vector<Move> history;

    public:
    MoveHistory() = default;
    [[nodiscard]] std::optional<Move> get_last_move() const;
    void push_move(const Move& move);
    Move& peek_last();
    void remove_last();
    bool piece_has_moved (const Piece* piece) const;
};


#endif //CCHESS_MOVEHISTORY_H