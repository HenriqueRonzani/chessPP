//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_BOARD_H
#define CCHESS_BOARD_H

#include <string>
#include "../ChessTypes.h"

class Piece;

enum class CastleDirection {
    KingSide = 0,
    QueenSide = 1
};

class Board {
    void move_piece(Position from, Position to);
    void undo_move_piece(Position from, Position to);
    void update_king_position(Position new_position, PieceColor king_color);
    void revoke_castle(CastleDirection castle_direction, PieceColor king_color);
public:
    const Piece* grid[8][8];
    GameState state;

    Board();
    void reset_board();
    void handle_move(const Move &move);
    void undo_move(const Move &move);
    void update_game_state(const Move& move);

    bool can_castle(CastleDirection castle_direction, PieceColor piece_color) const;

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] const Piece* piece_at_position(Position position) const;
};


#endif //CCHESS_BOARD_H