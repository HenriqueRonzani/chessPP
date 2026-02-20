//
// Created by global on 23/01/2026.
//

#include "Interpreter.h"

#include <algorithm>
#include <ranges>

#include "./MoveHistory.h"
#include <stdexcept>

constexpr Position whiteKingStart = { 4, 0 };
constexpr Position blackKingStart = { 4, 7 };

Move Interpreter::parse(const std::string_view &moveString, const Board& board) {
    const PieceColor pieceColor = board.history.getNextMoveColor();

    if (moveString == "O-O" || moveString == "O-O-O")
        return handleCastling(pieceColor, board, moveString);

    std::vector<Token> tokens;
    for (const char character : moveString) tokens.emplace_back(character);

    return resolveMove(tokens, pieceColor, board, moveString);
}

Move Interpreter::handleCastling(const PieceColor pieceColor, const Board &board, const std::string_view moveString) {
    const int moveDirection = moveString == "O-O" ? 2 : -2;

    const Position kingPosition = pieceColor == PieceColor::White
        ? whiteKingStart
        : blackKingStart;

    const Position target = {kingPosition.x + moveDirection, kingPosition.y};

    const Piece* king = board.atPosition(kingPosition);
    if (!king || king->kind != PieceKind::King || !king->isValidMove(kingPosition, target, board))
        throw std::invalid_argument("Invalid castle");


    return {
        .moveText = std::string(moveString),
        .movedPiece = king,
        .capturedPiece = nullptr,
        .from = kingPosition,
        .to = target,
        .isCastling = true,
        .promotionType = PieceKind::None,
        .isEnPassant = false
    };
}

Move Interpreter::resolveMove(std::vector<Token>& tokens, const PieceColor pieceColor, const Board& board, const std::string_view moveString) {
    const PieceKind pieceKind = tokens[0].type == TokenType::Piece
        ? getPieceKind(tokens[0].value)
        : PieceKind::Pawn;

    const auto [target, itTargetRow] = parseTarget(tokens);
    const auto [originColumn, originRow] = parseDisambiguation(tokens, itTargetRow);

    const Position fromPosition = board.findMoveablePiece(target, pieceKind, pieceColor, originColumn, originRow);

    const auto [isEnPassant, promotionType, enPassantVictim] = resolvePawnMove(tokens, target, fromPosition, board);
    Piece* capturedPiece = isEnPassant ? enPassantVictim : board.atPosition(target);

    if (promotionType == PieceKind::None && (target.y == 0 || target.y == 7) && pieceKind == PieceKind::Pawn)
        throw std::invalid_argument("Invalid Promotion Type");e4

    return {
        .moveText = std::string(moveString),
        .movedPiece = board.atPosition(fromPosition),
        .capturedPiece = capturedPiece,
        .from = fromPosition,
        .to = target,
        .isCastling = false,
        .promotionType = promotionType,
        .isEnPassant = isEnPassant
    };
}

Target Interpreter::parseTarget(std::vector<Token> &tokens) {
    const auto itTargetRow = std::ranges::find_if(tokens | std::views::reverse, [](const Token& t) {
           return t.type == TokenType::Row;
       });

    if (itTargetRow == tokens.rend()) throw std::invalid_argument("Invalid move input");
    const char rank = itTargetRow->value;
    const char col = std::next(itTargetRow)->value;

    return {
        .target = {col - 'a', rank - '1'},
        .itTargetRow = itTargetRow
    };
}

Position Interpreter::parseDisambiguation(std::vector<Token>& tokens, const TokenIt& itTargetRow) {
    const int originStart = tokens[0].type == TokenType::Piece ? 1 : 0;
    const auto originEnd = std::distance(tokens.begin(), itTargetRow.base()) - 2;
    int originRow = -1, originColumn = -1;

    for (int i = originStart; i < originEnd; i++) {
        const auto& t = tokens[i];
        if (t.type == TokenType::Column) originColumn = t.value - 'a';
        else if (t.type == TokenType::Row) originRow = t.value - '1';
    }
    return {
        originColumn,
        originRow
    };
}

PawnMoveContext Interpreter::resolvePawnMove(std::vector<Token> &tokens, const Position target, const Position piecePosition, const Board& board) {
    PieceKind promotionType = PieceKind::None;
    bool isEnPassant = false;
    Piece* enPassantVictim = nullptr;

    auto itPromotion = std::ranges::find(tokens, TokenType::Promotion, &Token::type);
    if (itPromotion != tokens.end()) {
        promotionType = getPieceKind(std::next(itPromotion)->value);
    }
    if (isCapture(tokens) && !board.atPosition(target)) {
        isEnPassant = true;
        enPassantVictim = board.atPosition({target.x, piecePosition.y});
    }

    return {
        .isEnPassant = isEnPassant,
        .promotionType = promotionType,
        .enPassantVictim = enPassantVictim
    };
}

PieceKind Interpreter::getPieceKind(const char p) {
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
