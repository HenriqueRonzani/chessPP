//
// Created by global on 23/01/2026.
//

#ifndef CCHESS_INTERPRETER_H
#define CCHESS_INTERPRETER_H
#include <ranges>
#include "Token.h"
#include "./MoveHistory.h"
#include "../board/Board.h"

using TokenIt = std::ranges::borrowed_iterator_t<std::ranges::reverse_view<std::ranges::ref_view<std::vector<Token>>>>;

struct Target {
    const Position target;
    TokenIt it_target_row;
};

struct PawnMoveContext {
    bool is_en_passant = false;
    PieceKind promotion_type = PieceKind::None;
    const Piece* en_passant_victim = nullptr;
};

class Interpreter {
    static Move resolve_move(std::vector<Token> &tokens, PieceColor piece_color, Board &board, std::string_view move_string);
    static Move resolve_castle_move(PieceColor piece_color, const Board &board, std::string_view move_string);
    static PawnMoveContext resolve_pawn_move(std::vector<Token> &tokens, Position target, Position piece_position, const Board &board);
    static Target resolve_target(std::vector<Token> &tokens);
    static Position resolve_disambiguation(std::vector<Token>& tokens, const TokenIt& it_target_row);
    static PieceKind get_piece_kind_from_char(char p);
    static bool is_capturing(const std::vector<Token>& tokens);

public:
    static Move parse_string(const std::string_view &move_string, Board &board, PieceColor moving_color);
};


#endif //CCHESS_INTERPRETER_H