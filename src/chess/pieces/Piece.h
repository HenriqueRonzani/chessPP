//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_PIECE_H
#define CCHESS_PIECE_H
#include "../board/Board.h"
#include "../move/MoveHistory.h"

class Board;

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
    black,
    white
};

class Piece {
protected:
    [[nodiscard]] std::vector<Position> generateSlidingMoves(Position pos, const Board& board, const std::vector<Position>& moveDirections, int maxSteps = 8) const;
public:
    PieceColor color;
    PieceKind kind;
    Piece(const PieceKind k, const PieceColor c) : color(c), kind(k) {} ;

    [[nodiscard]] char toChar() const;
    bool isEnemy(const Piece* piece) const;
    virtual ~Piece() = default;
    [[nodiscard]] virtual bool isValidMove(Position from, Position to, const Board& board) const;
    [[nodiscard]] virtual std::vector<Position> generateMoves(Position pos, const Board& board) const = 0;

    static PieceColor getOpposingColor (PieceColor color);
};


#endif //CCHESS_PIECE_H