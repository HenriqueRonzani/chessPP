//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_BOARD_H
#define CCHESS_BOARD_H
#include "Position.h"
#include <string>
#include "../move/MoveHistory.h"
#include "../pieces/Piece.h"

class Piece;

class Board {
    Piece* grid[8][8];
    Position whiteKingPos = {0, 6};
    Position blackKingPos = {7, 6};

    void handleCastle(const Move& move);
    void movePiece(Position from, Position to);
    [[nodiscard]] bool scanForAttackers(Position pos, PieceColor pieceColor, const std::vector<Position> &moveDirections, std::initializer_list<PieceKind> kinds,
        int maxSteps = 8) const;
    void filterLegalMoves(Position from, std::vector<Position>& pseudoLegalPositions);
public:
    Board();
    MoveHistory history;
    void resetBoard();
    void handleMove(const std::string& moveString);
    [[nodiscard]] std::string toString() const;
    [[nodiscard]] Piece* atPosition(Position position) const;
    [[nodiscard]] Position findMoveablePiece (Position target, PieceKind kind, PieceColor color, int pieceColumn = -1, int pieceRow = -1) const;

    [[nodiscard]] bool isSquareAttacked(const Position& position, PieceColor pieceColor) const;
    [[nodiscard]] bool isKingAttacked(PieceColor pieceColor) const;
    bool isMoveLegal(Position from, Position to);
    [[nodiscard]] bool hasLegalMoves(PieceColor pieceColor) const;
};


#endif //CCHESS_BOARD_H