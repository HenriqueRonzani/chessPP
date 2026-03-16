//
// Created by ronzani on 3/16/26.
//

#ifndef CCHESS_ENGINE_H
#define CCHESS_ENGINE_H
#include "board/Board.h"
#include "move/Interpreter.h"

class Engine {
    Board board;
    PieceColor moving_color = PieceColor::White;
public:
    Engine() { board.reset_board(); }
    [[nodiscard]] std::string get_board_to_string() const { return board.to_string(); }
    void make_move (const std::string& move_string) {
        const Move move = Interpreter::parse_string(move_string, board, moving_color);
        board.handle_move(move, moving_color);
        moving_color = PieceTypeHelper::get_opposite_color(moving_color);
    }
    [[nodiscard]] std::string get_moving_color_name () const { return PieceTypeHelper::get_color_name(moving_color); }
    [[nodiscard]] bool is_king_attacked () const { return board.is_king_attacked(moving_color); }
    bool is_game_over () { return !board.has_legal_moves(moving_color); }
};

#endif //CCHESS_ENGINE_H