//
// Created by ronzani on 3/21/26.
//

#ifndef CCHESS_TYPES_H
#define CCHESS_TYPES_H

#include <cmath>
#include <optional>
#include <string>

class Piece;

struct Position {
    int x, y;

    [[nodiscard]] bool is_valid() const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    [[nodiscard]] bool is_adjacent(const Position& pos) const {
        return abs(x - pos.x) == 1 && y - pos.y == 0;
    }

    bool operator==(const Position& pos) const {
        return x == pos.x && y == pos.y;
    }

    bool operator!=(const Position& pos) const {
        return x != pos.x || y != pos.y;
    }
};

static constexpr Position WHITE_KING_START = { 4, 0 };
static constexpr Position BLACK_KING_START = { 4, 7 };

enum class PieceKind {
    King,
    Queen,
    Rook,
    Knight,
    Bishop,
    Pawn,
    None
};

enum class PieceColor {
    White = 0,
    Black = 1,
    None
};

struct GameState {
    Position white_king_pos = WHITE_KING_START;
    Position black_king_pos = BLACK_KING_START;
    std::optional<Position> en_passant_target;

    // can_castle[PieceColor][CastleDirection]
    bool can_castle [2][2] {
        //  White
        {
            true, // KingSide
            true // QueenSide
        },
        // Black
        {
            true, // KingSide
            true  // QueenSide
        }
    };
};

struct Move {
    std::string move_string;
    const Piece* moved_piece;
    const Piece* captured_piece = nullptr;
    Position moved_from_position;
    Position moved_to_position;

    bool is_castle = false;
    bool is_en_passant = false;
    PieceKind promotion_type = PieceKind::None;
    GameState previous_state;
};

#endif //CCHESS_TYPES_H