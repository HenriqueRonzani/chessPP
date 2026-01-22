//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_PIECE_H
#define CCHESS_PIECE_H
#include "../board/Board.h"
#include "../move/MoveHistory.h"

class Board;

enum class PieceKind {
    king,
    queen,
    rook,
    knight,
    bishop,
    pawn
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
    Piece(PieceKind k, PieceColor c) : color(c), kind(k) {} ;

    [[nodiscard]] char toChar() const;
    bool isEnemy(const Piece* piece) const;
    virtual ~Piece() = default;
    virtual bool isValidMove(Position from, Position to, Board& board);

    virtual std::vector<Position> generateMoves(Position pos, Board& board);
};


#endif //CCHESS_PIECE_H