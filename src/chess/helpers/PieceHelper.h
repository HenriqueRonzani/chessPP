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
            case PieceKind::King:   return "King";
            case PieceKind::Queen:  return "Queen";
            case PieceKind::Rook:   return "Rook";
            case PieceKind::Knight: return "Knight";
            case PieceKind::Bishop: return "Bishop";
            case PieceKind::Pawn:   return "Pawn";
            default:                return "-";
        }
    }
    static std::string get_color_name(const PieceColor color) {
        switch (color) {
            case PieceColor::White: return "White";
            case PieceColor::Black: return "Black";
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