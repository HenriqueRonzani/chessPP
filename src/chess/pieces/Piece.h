//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_PIECE_H
#define CCHESS_PIECE_H
#include "PieceTypes.h"
#include "../board/Board.h"
#include "../move/MoveHistory.h"

class Board;

class Piece {
protected:
    [[nodiscard]] std::vector<Position> generate_sliding_moves(Position pos, const Board& board, const std::vector<Position>& move_directions, int max_steps = 8) const;
    PieceColor color;
    PieceKind kind;
public:
    Piece(const PieceKind k, const PieceColor c) : color(c), kind(k) {}

    static Piece* create(PieceKind piece_kind, PieceColor color);
    virtual ~Piece() = default;

    [[nodiscard]] PieceColor get_color () const;
    [[nodiscard]] PieceKind get_kind () const;
    [[nodiscard]] char to_char() const;

    [[nodiscard]] bool is_enemy(const Piece* piece) const;
    [[nodiscard]] bool is_enemy(const PieceColor& piece_color) const;

    [[nodiscard]] virtual bool is_movement_pseudo_legal(Position from, Position to, const Board& board) const;
    [[nodiscard]] virtual std::vector<Position> generate_pseudo_legal_moves(Position pos, const Board& board) const = 0;
};


#endif //CCHESS_PIECE_H