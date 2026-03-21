//
// Created by global on 20/01/2026.
//

#include "Piece.h"

#include <algorithm>
#include <stdexcept>

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "../board/Board.h"

char Piece::to_char() const {
    char kind_char;
    switch (kind) {
        case PieceKind::King:   kind_char = 'k'; break;
        case PieceKind::Queen:  kind_char = 'q'; break;
        case PieceKind::Rook:   kind_char = 'r'; break;
        case PieceKind::Knight: kind_char = 'n'; break;
        case PieceKind::Bishop: kind_char = 'b'; break;
        case PieceKind::Pawn:   kind_char = 'p'; break;
        default:                kind_char = '-'; break;
    }
    return color == PieceColor::White
        ? static_cast<char>(std::toupper(static_cast<unsigned char>(kind_char)))
        : kind_char;
}

PieceColor Piece::get_color() const {
    return color;
}

PieceKind Piece::get_kind() const {
    return kind;
}

bool Piece::is_enemy(const Piece* piece) const {
    return piece->color != color;
}

bool Piece::is_enemy(const PieceColor &piece_color) const {
    return piece_color != color;
}

bool Piece::is_movement_pseudo_legal(const Position from, Position to, const Board& board) const {
    const std::vector<Position> pseudo_legal_moves = generate_pseudo_legal_moves(from, board);
    return std::ranges::any_of(pseudo_legal_moves, [&](const auto& move) {
        return move == to;
    });
}

std::vector<Position> Piece::generate_sliding_moves(const Position pos, const Board &board, const std::vector<Position>& move_directions, const int max_steps) const {
    std::vector<Position> pseudo_legal_moves;
    for (const Position& dir : move_directions) {
        for (int i = 1; i <= max_steps; i++) {
            const Position move = { pos.x + dir.x * i, pos.y + dir.y * i };
            if (!move.is_valid()) break;

            const Piece* piece_at_position = board.piece_at_position(move);
            if (piece_at_position == nullptr) {
                pseudo_legal_moves.push_back(move);
            } else {
                if (piece_at_position->is_enemy(this)) {
                    pseudo_legal_moves.push_back(move);
                }
                break;
            }
        }
    }

    return pseudo_legal_moves;
}

Piece *Piece::create(const PieceKind piece_kind, const PieceColor color) {
    switch (piece_kind) {
        case PieceKind::Pawn: return new Pawn(color);
        case PieceKind::Rook: return new Rook(color);
        case PieceKind::Knight: return new Knight(color);
        case PieceKind::Bishop: return new Bishop(color);
        case PieceKind::King: return new King(color);
        case PieceKind::Queen: return new Queen(color);
        default: throw std::invalid_argument("Invalid New Piece Creation");
    }
}
