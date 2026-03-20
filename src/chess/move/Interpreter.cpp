//
// Created by global on 23/01/2026.
//

#include "Interpreter.h"

#include <algorithm>
#include <ranges>

#include "./MoveHistory.h"
#include <stdexcept>

#include "../helpers/BoardRules.h"

Move Interpreter::parse_string(const std::string_view &move_string, Board& board, const PieceColor moving_color) {
    Move move;

    if (move_string == "O-O" || move_string == "O-O-O") {
        move = resolve_castle_move(moving_color, board, move_string);
    } else {
        std::vector<Token> tokens = Token::string_to_token(move_string);
        move = resolve_move(tokens, moving_color, board, move_string);
    }

    if (!chess::rules::is_move_legal(board, move.moved_from_position, move.moved_to_position))
        throw std::invalid_argument("Illegal move");
    return move;
}

Move Interpreter::resolve_castle_move(const PieceColor piece_color, const Board &board, const std::string_view move_string) {
    const int castle_x_diff = move_string.length() == 3 ? 2 : -2;

    const Position king_position = piece_color == PieceColor::White
        ? WHITE_KING_START
        : BLACK_KING_START;

    const Position target = {king_position.x + castle_x_diff, king_position.y};

    const Piece* king = board.piece_at_position(king_position);
    if (!king || king->get_kind() != PieceKind::King || !king->is_movement_pseudo_legal(king_position, target, board))
        throw std::invalid_argument("Invalid castle");

    return {
        .move_string = std::string(move_string),
        .moved_piece = king,
        .captured_piece = nullptr,
        .moved_from_position = king_position,
        .moved_to_position = target,
        .is_castle = true,
        .is_en_passant = false,
        .promotion_type = PieceKind::None
    };
}

Move Interpreter::resolve_move(std::vector<Token>& tokens, const PieceColor piece_color, const Board& board, const std::string_view move_string) {
    const PieceKind piece_kind = tokens[0].type == TokenType::Piece
        ? get_piece_kind_from_char(tokens[0].value)
        : PieceKind::Pawn;

    const auto [target, it_target_row] = resolve_target(tokens);
    const auto [origin_column, origin_row] = resolve_disambiguation(tokens, it_target_row);

    const Position from_position = chess::rules::find_moveable_to_target(target, piece_kind, piece_color, origin_column, origin_row);

    const auto [is_en_passant, promotion_type, en_passant_victim] = resolve_pawn_move(tokens, target, from_position, board);
    const Piece* capturedPiece = is_en_passant ? en_passant_victim : board.piece_at_position(target);

    if (promotion_type == PieceKind::None && (target.y == 0 || target.y == 7) && piece_kind == PieceKind::Pawn)
        throw std::invalid_argument("Invalid Promotion Type");

    return {
        .move_string = std::string(move_string),
        .moved_piece = board.piece_at_position(from_position),
        .captured_piece = capturedPiece,
        .moved_from_position = from_position,
        .moved_to_position = target,
        .is_castle = false,
        .is_en_passant = is_en_passant,
        .promotion_type = promotion_type
    };
}

Target Interpreter::resolve_target(std::vector<Token> &tokens) {
    const auto it_target_row = std::ranges::find_if(tokens | std::views::reverse, [](const Token& t) {
           return t.type == TokenType::Row;
       });

    if (it_target_row == tokens.rend()) throw std::invalid_argument("Invalid move input");
    const char rank = it_target_row->value;
    const char col = std::next(it_target_row)->value;

    return {
        .target = {col - 'a', rank - '1'},
        .it_target_row = it_target_row
    };
}

Position Interpreter::resolve_disambiguation(std::vector<Token>& tokens, const TokenIt& it_target_row) {
    const int origin_start = tokens[0].type == TokenType::Piece ? 1 : 0;
    const auto origin_end = std::distance(tokens.begin(), it_target_row.base()) - 2;
    int origin_row = -1, origin_column = -1;

    for (int i = origin_start; i < origin_end; i++) {
        const auto& t = tokens[i];
        if (t.type == TokenType::Column) origin_column = t.value - 'a';
        else if (t.type == TokenType::Row) origin_row = t.value - '1';
    }
    return {
        origin_column,
        origin_row
    };
}

PawnMoveContext Interpreter::resolve_pawn_move(std::vector<Token> &tokens, const Position target, const Position piece_position, const Board& board) {
    PieceKind promotion_type = PieceKind::None;
    bool is_en_passant = false;
    const Piece* en_passant_victim = nullptr;

    auto it_promotion = std::ranges::find(tokens, TokenType::Promotion, &Token::type);
    if (it_promotion != tokens.end()) {
        promotion_type = get_piece_kind_from_char(std::next(it_promotion)->value);
    }
    if (is_capturing(tokens) && !board.piece_at_position(target)) {
        is_en_passant = true;
        en_passant_victim = board.piece_at_position({target.x, piece_position.y});
    }

    return {
        .is_en_passant = is_en_passant,
        .promotion_type = promotion_type,
        .en_passant_victim = en_passant_victim
    };
}

PieceKind Interpreter::get_piece_kind_from_char(const char p) {
    switch (std::toupper(p)) {
        case 'P': return PieceKind::Pawn;
        case 'R': return PieceKind::Rook;
        case 'N': return PieceKind::Knight;
        case 'B': return PieceKind::Bishop;
        case 'Q': return PieceKind::Queen;
        case 'K': return PieceKind::King;
        default: return PieceKind::None;
    }
}

bool Interpreter::is_capturing(const std::vector<Token>& tokens) {
    return std::ranges::any_of(tokens, [&](const auto item) {
        return item.type == TokenType::Action;
    });
}
