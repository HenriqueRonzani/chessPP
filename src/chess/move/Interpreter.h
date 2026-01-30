//
// Created by global on 23/01/2026.
//

#ifndef CCHESS_INTERPRETER_H
#define CCHESS_INTERPRETER_H
#include <string>
#include "Token.h"
#include "./MoveHistory.h"
#include "../board/Board.h"

class Interpreter {
    static bool isCapture(const std::vector<Token>& tokens);
    static Move findPieceFromTokens(std::vector<Token> &tokens, PieceColor pieceColor, const Board &board, std::string_view moveString);
    static PieceKind getPieceKindFromMove(char p);

public:
    static Move parse(const std::string_view &moveString, const Board& board);
};


#endif //CCHESS_INTERPRETER_H