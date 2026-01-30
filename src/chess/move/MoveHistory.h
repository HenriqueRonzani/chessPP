//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_MOVEHISTORY_H
#define CCHESS_MOVEHISTORY_H
#include <optional>
#include <string>
#include <vector>
#include "../board/Position.h"
#include "../pieces/PieceTypes.h"

class Piece;

struct Move {
    std::string moveText;
    const Piece* movedPiece;
    const Piece* capturedPiece = nullptr;
    Position from;
    Position to;

    bool isCastling = false;
    PieceKind promotionType = PieceKind::None;
    bool isEnPassant = false;
};

class MoveHistory {
    std::vector<Move> history;

    public:
    MoveHistory() = default;
    [[nodiscard]] std::optional<Move> getLastMove() const;
    void pushMove(const Move& move);
    [[nodiscard]] PieceColor getNextMoveColor() const;
};


#endif //CCHESS_MOVEHISTORY_H