//
// Created by ronzani on 1/17/26.
//

#include "Board.h"

#include <set>
#include <stdexcept>

#include "../pieces/Bishop.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"
#include "../pieces/Pawn.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"
#include "./Position.h"
#include "../helpers/BoardRules.h"
#include "../move/Interpreter.h"

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

    if (move.moved_piece->get_kind() == PieceKind::King) {
        if (move.moved_piece->get_color() == PieceColor::White) {
            state.white_king_pos = move.moved_to_position;
        } else {
            state.black_king_pos = move.moved_to_position;
        }
    }

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
    // TODO: implement update game state
}

bool Board::can_castle_long(const PieceColor color) const {
    return color == PieceColor::White
        ? state.white_can_castle_queen_side
        : state.black_can_castle_queen_side;
}

bool Board::can_castle_short(const PieceColor color) const {
    return color == PieceColor::White
        ? state.black_can_castle_queen_side
        : state.white_can_castle_queen_side;
}

