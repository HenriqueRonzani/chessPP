//
// Created by global on 30/01/2026.
//

#ifndef CCHESS_PIECETYPES_H
#define CCHESS_PIECETYPES_H

#include <string>

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
    White,
    Black
};

namespace PieceTypeHelper {
    static std::string getKindName(const PieceKind kind) {
        switch (kind) {
            case PieceKind::King:   return "King";
            case PieceKind::Queen:  return "Queen";
            case PieceKind::Rook:   return "Rook";
            case PieceKind::Knight: return "Knight";
            case PieceKind::Bishop: return "Bishop";
            case PieceKind::Pawn:   return "Pawn";
            default:                return "-";
        }
    }
    static std::string getColorName(const PieceColor color) {
        switch (color) {
            case PieceColor::White: return "White";
            case PieceColor::Black: return "Black";
            default:                return "-";
        }
    }
}

#endif //CCHESS_PIECETYPES_H