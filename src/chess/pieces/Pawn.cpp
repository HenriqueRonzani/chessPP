//
// Created by ronzani on 1/17/26.
//

#include "Pawn.h"

std::vector<Position> Pawn::generateMoves(const Position pos, Board& board) {
    const int movementDirection = color == PieceColor::white ? 1 : -1;
    const int startRow = color == PieceColor::white ? 1 : 6;

    std::vector<Position> possibleMoves;

    const Position moveForward = { pos.x, pos.y + movementDirection };
    if (moveForward.isValid() && board.atPosition(moveForward) == nullptr) {
        possibleMoves.push_back(moveForward);

        const Position doubleForward = { pos.x, pos.y + movementDirection * 2 };
        if (pos.y == startRow && doubleForward.isValid() && board.atPosition(doubleForward) == nullptr) {
            possibleMoves.push_back(doubleForward);
        }
    }

    for (const int xShift : { 1, -1 }) {
        const Position capturePosition = { pos.x + xShift, pos.y + movementDirection};
        if (capturePosition.isValid()) {
            const Piece* pieceAtPosition = board.atPosition(capturePosition);
            if (pieceAtPosition != nullptr && pieceAtPosition->isEnemy(this)) {
                possibleMoves.push_back(capturePosition);
            }
        }
    }

    return possibleMoves;
}