//
// Created by ronzani on 1/17/26.
//

#include "Board.h"

#include <iostream>
#include <set>
#include <stdexcept>

#include "../helpers/BoardHelper.h"
#include "../pieces/Bishop.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"
#include "../pieces/Pawn.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"


void Board::reset_board() {
    for (auto & i : grid) {
        for (auto & j : i) {
            delete j;
            j = nullptr;
        }
    }
    for (int j = 0; j < 8; j++) {
        grid[1][j] = new Pawn(PieceColor::White);
        grid[6][j] = new Pawn(PieceColor::Black);
    }
    grid[0][0] = new Rook(PieceColor::White);
    grid[0][1] = new Knight(PieceColor::White);
    grid[0][2] = new Bishop(PieceColor::White);
    grid[0][3] = new Queen(PieceColor::White);
    grid[0][4] = new King(PieceColor::White);
    grid[0][5] = new Bishop(PieceColor::White);
    grid[0][6] = new Knight(PieceColor::White);
    grid[0][7] = new Rook(PieceColor::White);

    grid[7][0] = new Rook(PieceColor::Black);
    grid[7][1] = new Knight(PieceColor::Black);
    grid[7][2] = new Bishop(PieceColor::Black);
    grid[7][3] = new Queen(PieceColor::Black);
    grid[7][4] = new King(PieceColor::Black);
    grid[7][5] = new Bishop(PieceColor::Black);
    grid[7][6] = new Knight(PieceColor::Black);
    grid[7][7] = new Rook(PieceColor::Black);

    state.white_king_pos = WHITE_KING_START;
    state.black_king_pos = BLACK_KING_START;
}

Board::Board() : grid{} {
    reset_board();
}

const Piece* Board::piece_at_position(const Position position) const {
    if (position.is_valid())
        return grid[position.y][position.x];
    return nullptr;
}

std::string Board::to_string() const {
    std::string boardString;
    for (int i = 7; i >= 0; i--) {
        boardString += std::to_string(i) + " ";
        for (int j = 0; j < 8; j++) {
            if (const Piece* piece = grid[i][j]; piece != nullptr)
                boardString += piece->to_char();
            else
                boardString += "-";
            boardString += " ";
        }
        boardString += "\n";
    }
    return boardString;
}

void Board::move_piece(const Position from, const Position to) {
    grid[to.y][to.x] = grid[from.y][from.x];
    grid[from.y][from.x] = nullptr;
}

void Board::undo_move_piece(const Position from, const Position to) {
    grid[from.y][from.x] = grid[to.y][to.x];
    grid[to.y][to.x] = nullptr;
}

void Board::handle_move(const Move& move) {
    move_piece(move.moved_from_position, move.moved_to_position);

    if (move.is_en_passant) {
        grid[move.moved_from_position.y][move.moved_to_position.x] = nullptr;
    }

    if (move.is_castle) {
        auto [origin, destination] = chess::rules::get_rook_castle_positions(move);
        move_piece(origin, destination);
    }

    if (move.promotion_type != PieceKind::None) {
        const Piece* promoted = Piece::create(move.promotion_type, move.moved_piece->get_color());
        grid[move.moved_to_position.y][move.moved_to_position.x] = promoted;
    }

    update_game_state(move);
}

void Board::undo_move(const Move& move){
    move_piece(move.moved_to_position, move.moved_from_position);

    if (move.moved_piece->get_kind() == PieceKind::King){
        if (move.moved_piece->get_color() == PieceColor::White){
            state.white_king_pos = move.moved_from_position;
        } else {
            state.black_king_pos = move.moved_from_position;
        }
    }

    if (move.is_en_passant) {
        grid[move.moved_from_position.y][move.moved_from_position.x] = move.captured_piece;
    } else {
        grid[move.moved_to_position.y][move.moved_to_position.x] = move.captured_piece;
    }

    if (move.is_castle) {
        auto [origin, destination] = chess::rules::get_rook_castle_positions(move);
        undo_move_piece(origin, destination);
    }

    if (move.promotion_type != PieceKind::None) {
        grid[move.moved_to_position.y][move.moved_to_position.x] = move.moved_piece;
    }

    state = move.previous_state;
}

void Board::update_game_state(const Move& move) {
    const bool is_pawn_double_move = move.moved_piece->get_kind() == PieceKind::Pawn &&
        abs(move.moved_to_position.x - move.moved_from_position.x) == 2;

    state.en_passant_target = is_pawn_double_move
        ? std::make_optional(move.moved_to_position)
        : std::nullopt;

    if (move.moved_piece->get_kind() == PieceKind::King) {
        const PieceColor king_color = move.moved_piece->get_color();
        update_king_position(move.moved_to_position, king_color);
        revoke_castle(CastleDirection::QueenSide, king_color);
        revoke_castle(CastleDirection::KingSide, king_color);
    }

    for (const auto rook_starting_positions =  std::vector<Position>{ {0, 0}, {0, 7}, {7, 0}, {7, 7} }; const auto position : rook_starting_positions) {
        const PieceColor color = position.x == 0 ? PieceColor::White : PieceColor::Black;
        const CastleDirection direction = position.y == 0 ? CastleDirection::QueenSide : CastleDirection::KingSide;

        if (
            move.moved_from_position == position ||
            move.moved_to_position == position
        ) {
            revoke_castle(direction, color);
            break;
        }
    }
}

void Board::update_king_position(const Position new_position, const PieceColor king_color) {
    if (king_color == PieceColor::White) {
        state.white_king_pos = new_position;
    } else {
        state.black_king_pos = new_position;
    }
}

void Board::revoke_castle(const CastleDirection castle_direction, const PieceColor king_color) {
    const int color_index = static_cast<int>(king_color);
    const int side_index  = static_cast<int>(castle_direction);
    state.can_castle[color_index][side_index] = false;
}

bool Board::can_castle(const CastleDirection castle_direction, const PieceColor piece_color) const {
    const int color_index = static_cast<int>(piece_color);
    const int side_index  = static_cast<int>(castle_direction);
    return state.can_castle[color_index][side_index];
}
