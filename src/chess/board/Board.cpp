//
// Created by ronzani on 1/17/26.
//

#include "Board.h"

#include <algorithm>
#include <set>
#include <stdexcept>

#include "../pieces/Bishop.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"
#include "../pieces/Pawn.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"
#include "./Position.h"
#include "../move/Interpreter.h"
#include <cmath>

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

    white_king_pos = white_king_start;
    black_king_pos = black_king_start;
}

Board::Board() : grid{} {
    reset_board();
}

Piece* Board::piece_at_position(const Position position) const {
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

Position Board::find_moveable_to_target(
    const Position target,
    const PieceKind kind,
    const PieceColor color,
    const int piece_column,
    const int piece_row
    ) const {
    std::vector<Position> moveable_pieces_positions;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Piece* piece = grid[j][i];
            if (!piece || piece->get_kind() != kind || piece->get_color() != color) continue;

            if (piece_column != -1 && piece_column != i) continue;
            if (piece_row != -1 && piece_row != j) continue;

            if (piece->is_movement_pseudo_legal({i, j}, target, *this)) {
                moveable_pieces_positions.emplace_back(i, j);
            }
        }
    }

    if (moveable_pieces_positions.empty())
        throw std::invalid_argument("No pieces are able to do this move");

    if (moveable_pieces_positions.size() > 1)
        throw std::invalid_argument("Multiple pieces are able to do this move");

    return moveable_pieces_positions[0];
}

void Board::move_piece(const Position from, const Position to) {
    grid[to.y][to.x] = grid[from.y][from.x];
    grid[from.y][from.x] = nullptr;
}

void Board::handle_castle(const Move &move) {
    const int rank = move.moved_piece->get_color() == PieceColor::White ? 0 : 7;
    const int rook_file = move.move_string == "O-O" ? 7 : 0;
    const Position rook_from = {rook_file, rank};
    const int destiny_file = (move.moved_from_position.x + move.moved_to_position.x)/2;
    const Position rook_to = {destiny_file, rank};
    move_piece(rook_from, rook_to);
}

void Board::handle_move(const Move& move, const PieceColor moving_color) {
    move_piece(move.moved_from_position, move.moved_to_position);

    if (move.moved_piece->get_kind() == PieceKind::King) {
        if (move.moved_piece->get_color() == PieceColor::White) {
            white_king_pos = move.moved_to_position;
        } else {
            black_king_pos = move.moved_to_position;
        }
    }
    if (move.is_en_passant) {
        grid[move.moved_from_position.y][move.moved_to_position.x] = nullptr;
    }

    if (move.is_castle) {
        handle_castle(move);
    }

    if (move.promotion_type != PieceKind::None) {
        Piece* promoted = Piece::create(move.promotion_type, move.moved_piece->get_color());
        grid[move.moved_to_position.y][move.moved_to_position.x] = promoted;
    }

    history.push_move(move);
}

bool Board::scan_for_attackers(const Position pos, const PieceColor piece_color, const std::vector<Position> &move_directions, const std::initializer_list<PieceKind> kinds, const int max_steps) const {
    for (const Position& dir : move_directions) {
        for (int i = 1; i <= max_steps; i++) {
            const Position current = { pos.x + dir.x * i, pos.y + dir.y * i };
            if (!current.is_valid()) break;

            if (const Piece* pieceAtPosition = piece_at_position(current)) {
                if (pieceAtPosition->is_enemy(piece_color)) {
                    for (const auto k : kinds)
                        if (pieceAtPosition->get_kind() == k)
                            return true;
                }
                break;
            }
        }
    }

    return false;
}

bool Board::is_square_attacked(const Position &pos, const PieceColor piece_color) const {
    static const std::vector<Position> diagDir = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    static const std::vector<Position> ortoDir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    static const std::vector<Position> knightDirections = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2},
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };

    if (scan_for_attackers(pos, piece_color, diagDir, {PieceKind::Bishop, PieceKind::Queen}))
        return true;
    if (scan_for_attackers(pos, piece_color, ortoDir, {PieceKind::Rook, PieceKind::Queen}))
        return true;
    if (scan_for_attackers(pos, piece_color, knightDirections, {PieceKind::Knight}, 1))
        return true;
    if (scan_for_attackers(pos, piece_color, diagDir, {PieceKind::King}, 1))
        return true;
    if (scan_for_attackers(pos, piece_color, ortoDir, {PieceKind::King}, 1))
        return true;

    const int enemyPawnDirection = piece_color == PieceColor::White ? 1 : -1;

    return std::ranges::any_of(std::array{ 1, -1 }, [&](const int xShift) {
        const Position pawnPos = { pos.x + xShift, pos.y + enemyPawnDirection};
        if (pawnPos.is_valid()) {
            const Piece* piece = piece_at_position(pawnPos);
            if (piece != nullptr && piece->is_enemy(piece_color) && piece->get_kind() == PieceKind::Pawn)
                return true;
        }
        return false;
    });
}

bool Board::is_square_free(const Position &pos) const {
    return !piece_at_position(pos);
}

bool Board::is_square_free_and_not_attacked(const Position &pos, const PieceColor piece_color) const {
    return is_square_free(pos) &&
        !is_square_attacked(pos, piece_color);
}


bool Board::is_king_attacked(const PieceColor piece_color) const {
    const Position kingPos = piece_color == PieceColor::White
        ? white_king_pos
        : black_king_pos;

    return is_square_attacked(kingPos, piece_color);
}

bool Board::is_move_legal(const Position from_position, const Position to_position) {
    Piece* piece_from = piece_at_position(from_position);
    Piece* piece_to = piece_at_position(to_position);
    const Position current_king_position = piece_from->get_color() == PieceColor::White
        ? white_king_pos
        : black_king_pos;

    const bool is_en_passant = piece_from->get_kind() == PieceKind::Pawn
        && to_position.x != from_position.x
        && !piece_to;
    const bool is_castling = piece_from->get_kind() == PieceKind::King
        && std::abs(to_position.x - from_position.x) == 2;

    Piece *enPassantPiece = piece_at_position({to_position.x, from_position.y});

    const int rank = piece_from->get_color() == PieceColor::White ? 0 : 7;
    const int rook_file = from_position.x < to_position.x ? 7 : 0;
    const Position rook_from = {rook_file, rank};
    const Position rook_to = {(from_position.x + to_position.x)/2, rank};

    // Simulate movement
    grid[to_position.y][to_position.x] = piece_from;
    grid[from_position.y][from_position.x] = nullptr;
    if (is_en_passant) grid[from_position.y][to_position.x] = nullptr;
    if (is_castling) {
        grid[rook_to.y][rook_to.x] = grid[rook_from.y][rook_from.x];
        grid[rook_from.y][rook_from.x] = nullptr;
    }
    if (piece_from->get_kind() == PieceKind::King) {
        if (piece_from->get_color() == PieceColor::White) white_king_pos = to_position;
        else black_king_pos = to_position;
    }

    const bool is_king_checked_after_move = is_king_attacked(piece_from->get_color());

    // Undo simulation
    grid[to_position.y][to_position.x] = piece_to;
    grid[from_position.y][from_position.x] = piece_from;
    if (is_en_passant) grid[from_position.y][to_position.x] = enPassantPiece;
    if (is_castling) {
        grid[rook_from.y][rook_from.x] = grid[rook_to.y][rook_to.x];
        grid[rook_to.y][rook_to.x] = nullptr;
    }
    if (piece_from->get_kind() == PieceKind::King) {
        if (piece_from->get_color() == PieceColor::White) white_king_pos = current_king_position;
        else black_king_pos = current_king_position;
    }

    return !is_king_checked_after_move;
}

void Board::filter_legal_destinations(Position from, std::vector<Position>& pseudo_legal_to_positions) {
    std::erase_if(pseudo_legal_to_positions, [from, this](const Position& pos) {
        return !is_move_legal(from, pos);
    });
}

bool Board::has_legal_moves(const PieceColor piece_color) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (const Piece* piece = grid[i][j];
                piece && piece->get_color() == piece_color) {
                std::vector<Position> positions = piece->generate_pseudo_legal_moves({j, i}, *this);
                filter_legal_destinations({j, i}, positions);
                if (!positions.empty()) return true;
            }
        }
    }
    return false;
}
