//
// Created by global on 20/01/2026.
//

#include "Piece.h"

#include <algorithm>

char Piece::toChar() const {
    char kindChar;
    switch (kind) {
        case PieceKind::King:   kindChar = 'k'; break;
        case PieceKind::Queen:  kindChar = 'q'; break;
        case PieceKind::Rook:   kindChar = 'r'; break;
        case PieceKind::Knight: kindChar = 'n'; break;
        case PieceKind::Bishop: kindChar = 'b'; break;
        case PieceKind::Pawn:   kindChar = 'p'; break;
        default:                kindChar = '-'; break;
    }
    return color == PieceColor::white
        ? static_cast<char>(std::toupper(static_cast<unsigned char>(kindChar)))
        : kindChar;
}

bool Piece::isEnemy(const Piece* piece) const {
    return piece->color != color;
}

bool Piece::isValidMove(const Position from, Position to, const Board& board) const {
    const std::vector<Position> validMoves = generateMoves(from, board);
    return std::ranges::any_of(validMoves, [&](const auto& move) {
        return move == to;
    });
}

std::vector<Position> Piece::generateSlidingMoves(const Position pos, const Board &board, const std::vector<Position>& moveDirections, const int maxSteps) const {
    std::vector<Position> possibleMoves;
    for (const Position& dir : moveDirections) {
        for (int i = 1; i <= maxSteps; i++) {
            const Position move = { pos.x + dir.x * i, pos.y + dir.y * i };
            if (!move.isValid()) break;

            const Piece* pieceAtPosition = board.atPosition(move);
            if (pieceAtPosition == nullptr) {
                possibleMoves.push_back(move);
            } else {
                if (pieceAtPosition->isEnemy(this)) {
                    possibleMoves.push_back(move);
                }
                break;
            }
        }
    }

    return possibleMoves;
}

std::vector<Position> Piece::generateMoves(const Position pos, const Board &board) const {
    return {};
}

PieceColor Piece::getOpposingColor(const PieceColor color) {
    return color == PieceColor::black
     ? PieceColor::white
     : PieceColor::black;
}
