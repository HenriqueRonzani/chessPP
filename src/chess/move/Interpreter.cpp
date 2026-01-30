//
// Created by global on 23/01/2026.
//

#include "Interpreter.h"

#include <algorithm>
#include <ranges>

#include "./MoveHistory.h"
#include <stdexcept>

constexpr std::string allowedPieces = "KQRBN";
constexpr std::string allowedColumns = "abcdefgh";
constexpr std::string allowedRanks = "12345678";
constexpr std::string allowedActions = "+#=";
constexpr std::string castleCharacters = "O-";
const std::string allowedChars = allowedPieces + allowedColumns + allowedRanks + allowedActions + castleCharacters;


Move Interpreter::parse(const std::string_view &moveString, const Board& board) {
    std::vector<Token> tokens;
    for (const char character : moveString) {
        tokens.emplace_back(character);
    }

    const PieceColor pieceColor = board.history.getNextMoveColor();

    return findPieceFromTokens(tokens, pieceColor, board, moveString);
}

Move Interpreter::findPieceFromTokens(std::vector<Token>& tokens, const PieceColor pieceColor, const Board& board, const std::string_view moveString) {
    const PieceKind pieceKind = tokens[0].type == TokenType::Piece
        ? getPieceKindFromMove(tokens[0].value)
        : PieceKind::Pawn;

    const auto itTargetRow = std::ranges::find_if(tokens | std::views::reverse, [](const Token& t) {
        return t.type == TokenType::Row;
    });

    if (itTargetRow == tokens.rend()) throw std::invalid_argument("Invalid move input");
    const char rank = itTargetRow->value;
    const char col = std::next(itTargetRow)->value;
    const Position target = {col - 'a', rank - '1'};

    const int originStart = tokens[0].type == TokenType::Piece ? 1 : 0;
    const auto originEnd = std::distance(tokens.begin(), itTargetRow.base()) - 2;

    int originRow = -1, originColumn = -1;

    for (int i = originStart; i < originEnd; i++) {
        const auto& t = tokens[i];
        if (t.type == TokenType::Column) originColumn = t.value - 'a';
        else if (t.type == TokenType::Row) originRow = t.value - '1';
    }

    const Position piecePosition = board.findMoveablePiece(target, pieceKind, pieceColor, originColumn, originRow);


    Piece* capturedPiece = board.atPosition(target);
    PieceKind promotionType = PieceKind::None;
    bool isEnPassant = false;

    if (pieceKind == PieceKind::Pawn) {
        auto itPromotion = std::ranges::find(tokens, TokenType::Promotion, &Token::type);
        if (itPromotion != tokens.end()) {
            promotionType = getPieceKindFromMove(std::next(itPromotion)->value);
        }
        if (isCapture(tokens) && !capturedPiece) {
            isEnPassant = true;
            capturedPiece = board.atPosition({target.x, piecePosition.y});
        }
    }

    return {
        .moveText = std::string(moveString),
        .movedPiece = board.atPosition(piecePosition),
        .capturedPiece = capturedPiece,
        .from = piecePosition,
        .to = target,
        .isCastling = false,
        .promotionType = promotionType,
        .isEnPassant = isEnPassant
    };
}

PieceKind Interpreter::getPieceKindFromMove(const char p) {
    switch (std::toupper(p)) {
        case 'P': return PieceKind::Pawn;
        case 'R': return PieceKind::Rook;
        case 'N': return PieceKind::Knight;
        case 'B': return PieceKind::Bishop;
        case 'Q': return PieceKind::Queen;
        case 'K': return PieceKind::King;
        default: return PieceKind::None;
    }
}

bool Interpreter::isCapture(const std::vector<Token>& tokens) {
    return std::ranges::any_of(tokens, [&](const auto item) {
        return item.type == TokenType::Action;
    });
}
