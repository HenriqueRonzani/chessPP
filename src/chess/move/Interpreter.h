//
// Created by global on 23/01/2026.
//

#ifndef CCHESS_INTERPRETER_H
#define CCHESS_INTERPRETER_H
#include <string>

#include "Token.h"
#include "../pieces/Piece.h"


class Interpreter {
    // bool parse(std::string moveString);
    bool validateCharacters(const std::string &moveString);
    // bool validateMove(Piece piece, Position position);
};


#endif //CCHESS_INTERPRETER_H