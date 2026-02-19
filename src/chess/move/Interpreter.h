//
// Created by global on 23/01/2026.
//

#ifndef CCHESS_INTERPRETER_H
#define CCHESS_INTERPRETER_H
#include <ranges>
#include "Token.h"
#include "./MoveHistory.h"
#include "../board/Board.h"

using TokenIt = std::ranges::borrowed_iterator_t<std::ranges::reverse_view<std::ranges::ref_view<std::vector<Token>>>>;

struct PieceOrigin {
    const int originRow;
    const int originColumn;
};

struct Target {
    const Position target;
    TokenIt itTargetRow;
};

struct PawnMoveContext {
    bool isEnPassant = false;
    PieceKind promotionType = PieceKind::None;
    Piece* enPassantVictim = nullptr;
};

class Interpreter {
    static Move resolveMove(std::vector<Token> &tokens, PieceColor pieceColor, const Board &board, std::string_view moveString);
    static Move handleCastling(PieceColor pieceColor, const Board &board, std::string_view moveString);
    static Position parseDisambiguation(std::vector<Token>& tokens, const TokenIt& itTargetRow);
    static Target parseTarget(std::vector<Token>& tokens);
    static PawnMoveContext resolvePawnMove(std::vector<Token> &tokens, Position target, Position piecePosition, const Board &board);
    static PieceKind getPieceKind(char p);
    static bool isCapture(const std::vector<Token>& tokens);

public:
    static Move parse(const std::string_view &moveString, const Board& board);
};


#endif //CCHESS_INTERPRETER_H