//
// Created by global on 20/01/2026.
//

#include "Piece.h"

bool Piece::isEnemy(const Piece* piece) const {
    return piece->color != color;
}

bool Piece::isValidMove(Position from, Position to, Board &board) {
    return false;
}

std::vector<Position> Piece::generateMoves(Position pos, Board &board) {
    return {};
}
