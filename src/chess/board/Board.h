//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_BOARD_H
#define CCHESS_BOARD_H
#include "Position.h"
#include <string>
#include "../move/MoveHistory.h"
#include "../pieces/Piece.h"

class Piece;

static constexpr Position WHITE_KING_START = { 4, 0 };
static constexpr Position BLACK_KING_START = { 4, 7 };

struct GameState {
    Position white_king_pos = WHITE_KING_START;
    Position black_king_pos = BLACK_KING_START;
    std::optional<Position> en_passant_target;
    bool white_can_castle_king_side = true;
    bool white_can_castle_queen_side = true;
    bool black_can_castle_king_side = true;
    bool black_can_castle_queen_side = true;
};

class Board {
    void move_piece(Position from, Position to);
    void undo_move_piece(Position from, Position to);

public:
    const Piece* grid[8][8];
    GameState state;

    Board();
    void reset_board();
    void handle_move(const Move &move);
    void undo_move(const Move &move);
    void update_game_state(const Move& move);

    [[nodiscard]] bool can_castle_long(PieceColor color) const;
    [[nodiscard]] bool can_castle_short(PieceColor color) const;

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] const Piece* piece_at_position(Position position) const;
};


#endif //CCHESS_BOARD_H