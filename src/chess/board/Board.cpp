//
// Created by ronzani on 1/17/26.
//

#include "Board.h"

#include <algorithm>
#include <set>
#include <stdexcept>

#include "../pieces/Bishop.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"
#include "../pieces/Pawn.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"
#include "./Position.h"
#include "../move/Interpreter.h"
#include <cmath>

void Board::resetBoard() {
    for (auto & i : grid) {
        for (auto & j : i) {
            delete j;
            j = nullptr;
        }
    }
    for (int j = 0; j < 8; j++) {
        grid[1][j] = new Pawn(PieceColor::White);
        grid[6][j] = new Pawn(PieceColor::Black);
    }
    grid[0][0] = new Rook(PieceColor::White);
    grid[0][1] = new Knight(PieceColor::White);
    grid[0][2] = new Bishop(PieceColor::White);
    grid[0][3] = new Queen(PieceColor::White);
    grid[0][4] = new King(PieceColor::White);
    grid[0][5] = new Bishop(PieceColor::White);
    grid[0][6] = new Knight(PieceColor::White);
    grid[0][7] = new Rook(PieceColor::White);

    grid[7][0] = new Rook(PieceColor::Black);
    grid[7][1] = new Knight(PieceColor::Black);
    grid[7][2] = new Bishop(PieceColor::Black);
    grid[7][3] = new Queen(PieceColor::Black);
    grid[7][4] = new King(PieceColor::Black);
    grid[7][5] = new Bishop(PieceColor::Black);
    grid[7][6] = new Knight(PieceColor::Black);
    grid[7][7] = new Rook(PieceColor::Black);

    whiteKingPos = { 4, 0 };
    blackKingPos = { 4, 7 };
}

Board::Board() : grid{} {
    resetBoard();
}

Piece* Board::atPosition(const Position position) const {
    if (position.isValid())
        return grid[position.y][position.x];
    return nullptr;
}

std::string Board::toString() const {
    std::string boardString;
    for (int i = 7; i >= 0; i--) {
        boardString += std::to_string(i) + " ";
        for (int j = 0; j < 8; j++) {
            if (const Piece* piece = grid[i][j]; piece != nullptr)
                boardString += piece->toChar();
            else
                boardString += "-";
            boardString += " ";
        }
        boardString += "\n";
    }
    return boardString;
}

Position Board::findMoveablePiece(
    const Position target,
    const PieceKind kind,
    const PieceColor color,
    const int pieceColumn,
    const int pieceRow
    ) const {
    std::vector<Position> moveablePiecesPositions;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Piece* piece = grid[j][i];
            if (!piece || piece->kind != kind || piece->color != color) continue;

            if (pieceColumn != -1 && pieceColumn != i) continue;
            if (pieceRow != -1 && pieceRow != j) continue;

            if (piece->isValidMove({i, j}, target, *this)) {
                moveablePiecesPositions.emplace_back(i, j);
            }
        }
    }

    if (moveablePiecesPositions.empty())
        throw std::invalid_argument("No pieces are able to do this move");

    if (moveablePiecesPositions.size() > 1)
        throw std::invalid_argument("Multiple pieces are able to do this move");

    return moveablePiecesPositions[0];
}

void Board::movePiece(const Position from, const Position to) {
    grid[to.y][to.x] = grid[from.y][from.x];
    grid[from.y][from.x] = nullptr;
}

void Board::handleCastle(const Move &move) {
    const int rank = move.movedPiece->color == PieceColor::White ? 0 : 7;
    const int rookFile = move.moveText == "O-O" ? 7 : 0;
    const Position rookFrom = {rookFile, rank};
    const int destinyFile = (move.from.x + move.to.x)/2;
    const Position rookTo = {destinyFile, rank};
    movePiece(rookFrom, rookTo);
}

void Board::handleMove(const std::string& moveString) {
    const Move move = Interpreter::parse(moveString, *this);
    if (move.movedPiece->kind == PieceKind::King) {
        movePiece(move.from, move.to);
    } else {
    movePiece(move.from, move.to);
    }

    if (move.movedPiece->kind == PieceKind::King) {
        if (move.movedPiece->color == PieceColor::White) {
            whiteKingPos = move.to;
        } else {
            blackKingPos = move.to;
        }
    }
    if (move.isEnPassant) {
        grid[move.from.y][move.to.x] = nullptr;
    }

    if (move.isCastling) {
        handleCastle(move);
    }

    if (move.promotionType != PieceKind::None) {
        Piece* promoted = Piece::create(move.promotionType, move.movedPiece->color);
        grid[move.to.y][move.to.x] = promoted;
    }

    history.pushMove(move);
}

bool Board::scanForAttackers(const Position pos, const PieceColor pieceColor, const std::vector<Position> &moveDirections, const std::initializer_list<PieceKind> kinds, const int maxSteps) const {
    for (const Position& dir : moveDirections) {
        for (int i = 1; i <= maxSteps; i++) {
            const Position current = { pos.x + dir.x * i, pos.y + dir.y * i };
            if (!current.isValid()) break;

            if (const Piece* pieceAtPosition = atPosition(current)) {
                if (pieceAtPosition->isEnemy(pieceColor)) {
                    for (const auto k : kinds)
                        if (pieceAtPosition->kind == k)
                            return true;
                }
                break;
            }
        }
    }

    return false;
}

bool Board::isSquareAttacked(const Position &position, const PieceColor pieceColor) const {
    static const std::vector<Position> diagDir = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    static const std::vector<Position> ortoDir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    static const std::vector<Position> knightDirections = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2},
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };

    if (scanForAttackers(position, pieceColor, diagDir, {PieceKind::Bishop, PieceKind::Queen}))
        return true;
    if (scanForAttackers(position, pieceColor, ortoDir, {PieceKind::Rook, PieceKind::Queen}))
        return true;
    if (scanForAttackers(position, pieceColor, knightDirections, {PieceKind::Knight}, 1))
        return true;
    if (scanForAttackers(position, pieceColor, diagDir, {PieceKind::King}, 1))
        return true;
    if (scanForAttackers(position, pieceColor, ortoDir, {PieceKind::King}, 1))
        return true;

    const int enemyPawnDirection = pieceColor == PieceColor::White ? 1 : -1;

    return std::ranges::any_of(std::array{ 1, -1 }, [&](const int xShift) {
        const Position pawnPos = { position.x + xShift, position.y + enemyPawnDirection};
        if (pawnPos.isValid()) {
            const Piece* piece = atPosition(pawnPos);
            if (piece != nullptr && piece->isEnemy(pieceColor) && piece->kind == PieceKind::Pawn)
                return true;
        }
        return false;
    });
}

bool Board::isKingAttacked(const PieceColor pieceColor) const {
    const Position kingPos = pieceColor == PieceColor::White
        ? whiteKingPos
        : blackKingPos;

    return isSquareAttacked(kingPos, pieceColor);
}

bool Board::isMoveLegal(const Position from, const Position to) {
    Piece* pieceFrom = atPosition(from);
    Piece* pieceTo = atPosition(to);

    const bool isEnPassant = pieceFrom->kind == PieceKind::Pawn
        && to.x != from.x
        && !pieceTo;
    const bool isCastling = pieceFrom->kind == PieceKind::King
        && std::abs(to.x - from.x) == 2;

    Piece *enPassantPiece = atPosition({to.x, from.y});

    // Simulate movement
    grid[to.y][to.x] = pieceFrom;
    grid[from.y][from.x] = nullptr;
    if (isEnPassant) grid[from.y][to.x] = nullptr;
    if (isCastling) {
        const int rank = pieceFrom->color == PieceColor::White ? 0 : 7;
        const int rookFile = from.x < to.x ? 7 : 0;
        const Position rookFrom = {rookFile, rank};
        const Position rookTo = {(from.x + to.x)/2, rank};

        grid[rookTo.y][rookTo.x] = grid[rookFrom.y][rookFrom.x];
        grid[rookFrom.y][rookFrom.x] = nullptr;
    }

    const bool isInCheck = isKingAttacked(pieceFrom->color);

    // Undo simulation
    grid[to.y][to.x] = pieceTo;
    grid[from.y][from.x] = pieceFrom;
    if (isEnPassant) grid[from.y][to.x] = enPassantPiece;
    if (isCastling) {
        const int rank = pieceFrom->color == PieceColor::White ? 0 : 7;
        const int rookFile = from.x < to.x ? 7 : 0;
        const Position rookFrom = {rookFile, rank};
        const Position rookTo = {(from.x + to.x)/2, rank};

        grid[rookFrom.y][rookFrom.x] = grid[rookTo.y][rookTo.x];
        grid[rookTo.y][rookTo.x] = nullptr;
    }

    return !isInCheck;
}

void Board::filterLegalMoves(Position from, std::vector<Position>& pseudoLegalPositions) {
    std::erase_if(pseudoLegalPositions, [from, this](const Position& pos) {
        return !isMoveLegal(from, pos);
    });
}

bool Board::hasLegalMoves(const PieceColor pieceColor) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (const Piece* piece = grid[i][j];
                piece && piece->color == pieceColor) {
                std::vector<Position> positions = piece->generateMoves({j, i}, *this);
                if (!positions.empty()) return true;
            }
        }
    }
    return false;
}
