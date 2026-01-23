//
// Created by global on 23/01/2026.
//

#include "Interpreter.h"

constexpr std::string allowedPieces = "KQRBN";
constexpr std::string allowedColumns = "abcdefgh";
constexpr std::string allowedRanks = "12345678";
constexpr std::string allowedActions = "+#=";
constexpr std::string castleCharacters = "O-";
const std::string allowedChars = allowedPieces + allowedColumns + allowedRanks + allowedActions + castleCharacters;


bool Interpreter::validateCharacters(const std::string &moveString) {
    std::vector<Token> tokens;
    for (const char character : moveString) {
        tokens.push_back(Token(character));
    }
    //
    // if (tokens.size() == 2) {
    //     return
    // }
}
