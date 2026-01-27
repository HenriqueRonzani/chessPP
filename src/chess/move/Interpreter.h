//
// Created by global on 23/01/2026.
//

#ifndef CCHESS_INTERPRETER_H
#define CCHESS_INTERPRETER_H
#include <string>
#include "Token.h"
#include "./MoveHistory.h"
#include "../pieces/Piece.h"


class Interpreter {
    static Move parse(const std::string_view &moveString, const MoveHistory& moveHistory, const Board& board);

    static bool isCapture(const std::vector<Token>& tokens);

    static Move findPieceFromTokens(std::vector<Token> &tokens, PieceColor pieceColor, const Board &board);
    static PieceKind getPieceKindFromMove(char p);

    // bool validateCharacters(const std::string &moveString);
    // bool validateMove(Piece piece, Position position);
};


#endif //CCHESS_INTERPRETER_H