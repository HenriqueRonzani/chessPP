//
// Created by ronzani on 3/21/26.
//

#ifndef CCHESS_PIECEHELPER_H
#define CCHESS_PIECEHELPER_H
#include <string>

#include "../ChessTypes.h"

namespace chess::piece_helper {
    static std::string get_kind_name(const PieceKind kind) {
        switch (kind) {
            case PieceKind::King:   return "king";
            case PieceKind::Queen:  return "queen";
            case PieceKind::Rook:   return "rook";
            case PieceKind::Knight: return "knight";
            case PieceKind::Bishop: return "bishop";
            case PieceKind::Pawn:   return "pawn";
            default:                return "-";
        }
    }
    static std::string get_color_name(const PieceColor color) {
        switch (color) {
            case PieceColor::White: return "white";
            case PieceColor::Black: return "black";
            default:                return "-";
        }
    }
    static PieceColor get_opposite_color(const PieceColor color) {
        switch (color) {
            case PieceColor::White: return PieceColor::Black;
            case PieceColor::Black: return PieceColor::White;
            default:                return PieceColor::None;
        }
    }
}


#endif //CCHESS_PIECEHELPER_H