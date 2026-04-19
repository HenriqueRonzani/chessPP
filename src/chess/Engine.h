//
// Created by ronzani on 3/16/26.
//

#ifndef CCHESS_ENGINE_H
#define CCHESS_ENGINE_H
#include "board/Board.h"
#include "move/Interpreter.h"
#include "helpers/BoardHelper.h"
#include "helpers/PieceHelper.h"

class Engine {
    Board board;
    PieceColor moving_color = PieceColor::White;
    MoveHistory history;

public:
    Engine() { board.reset_board(); }
    [[nodiscard]] std::string get_board_to_string() const { return board.to_string(); }
    void make_move (const std::string& move_string) {
        const Move move = Interpreter::parse_string(move_string, board, moving_color);
        board.handle_move(move);
        moving_color = chess::piece_helper::get_opposite_color(moving_color);
        history.push_move(move);
    }
    void undo_move () {
        board.undo_move(history.peek_last());
        moving_color = chess::piece_helper::get_opposite_color(moving_color);
        history.remove_last();
    }
    [[nodiscard]] std::string get_moving_color_name () const { return chess::piece_helper::get_color_name(moving_color); }
    [[nodiscard]] bool is_king_attacked () const { return chess::rules::is_king_attacked(board, moving_color); }
    bool is_game_over_by_fifty_move_rule () const { return !chess::rules::check_fifty_move_rule(history.get_history()); }
    bool is_game_over_by_checkmate_or_stalemate () { return !chess::rules::has_legal_moves(board, moving_color); }
};

#endif //CCHESS_ENGINE_H