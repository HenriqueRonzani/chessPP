//
// Created by ronzani on 19/03/2026.
//

#include "BoardRules.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace chess::rules {
    CastleRookPositions get_rook_castle_positions(const Move &move) {
        const int rank = move.moved_piece->get_color() == PieceColor::White ? 0 : 7;
        const int rook_file = move.move_string == "O-O" ? 7 : 0;
        const Position rook_from = {rook_file, rank};
        const int destiny_file = (move.moved_from_position.x + move.moved_to_position.x)/2;
        const Position rook_to = {destiny_file, rank};
        return { rook_from, rook_to };
    }

    Position find_moveable_to_target(
    const Board& board,
    const Position target,
    const PieceKind kind,
    const PieceColor color,
    const int piece_column,
    const int piece_row
    ) {
        std::vector<Position> moveable_pieces_positions;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                const Piece* piece = board.grid[j][i];
                if (!piece || piece->get_kind() != kind || piece->get_color() != color) continue;

                if (piece_column != -1 && piece_column != i) continue;
                if (piece_row != -1 && piece_row != j) continue;

                if (piece->is_movement_pseudo_legal({i, j}, target, *this)) {
                    moveable_pieces_positions.emplace_back(i, j);
                }
            }
        }

        if (moveable_pieces_positions.empty())
            throw std::invalid_argument("No pieces are able to do this move");

        if (moveable_pieces_positions.size() > 1)
            throw std::invalid_argument("Multiple pieces are able to do this move");

        return moveable_pieces_positions[0];
    }

    bool scan_for_attackers(const Board& board, const Position pos, const PieceColor piece_color, const std::vector<Position> &move_directions, const std::initializer_list<PieceKind> kinds, const int max_steps) {
        for (const Position& dir : move_directions) {
            for (int i = 1; i <= max_steps; i++) {
                const Position current = { pos.x + dir.x * i, pos.y + dir.y * i };
                if (!current.is_valid()) break;

                if (const Piece* pieceAtPosition = board.piece_at_position(current)) {
                    if (pieceAtPosition->is_enemy(piece_color)) {
                        for (const auto k : kinds)
                            if (pieceAtPosition->get_kind() == k)
                                return true;
                    }
                    break;
                }
            }
        }

        return false;
    }

    bool is_square_attacked(const Board& board, const Position &pos, const PieceColor piece_color) {
        static const std::vector<Position> diagDir = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
        static const std::vector<Position> ortoDir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        static const std::vector<Position> knightDirections = {
            {1, 2}, {2, 1}, {2, -1}, {1, -2},
            {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
        };

        if (scan_for_attackers(board, pos, piece_color, diagDir, {PieceKind::Bishop, PieceKind::Queen}))
            return true;
        if (scan_for_attackers(board, pos, piece_color, ortoDir, {PieceKind::Rook, PieceKind::Queen}))
            return true;
        if (scan_for_attackers(board, pos, piece_color, knightDirections, {PieceKind::Knight}, 1))
            return true;
        if (scan_for_attackers(board, pos, piece_color, diagDir, {PieceKind::King}, 1))
            return true;
        if (scan_for_attackers(board, pos, piece_color, ortoDir, {PieceKind::King}, 1))
            return true;

        const int enemyPawnDirection = piece_color == PieceColor::White ? 1 : -1;

        return std::ranges::any_of(std::array{ 1, -1 }, [&](const int xShift) {
            const Position pawnPos = { pos.x + xShift, pos.y + enemyPawnDirection};
            if (pawnPos.is_valid()) {
                const Piece* piece = board.piece_at_position(pawnPos);
                if (piece != nullptr && piece->is_enemy(piece_color) && piece->get_kind() == PieceKind::Pawn)
                    return true;
            }
            return false;
        });
    }

    bool is_square_free(const Board& board, const Position &pos) {
        return !board.piece_at_position(pos);
    }

    bool is_square_free_and_not_attacked(const Board& board, const Position& pos, const PieceColor piece_color) {
        return is_square_free(board, pos) &&
            !is_square_attacked(board, pos, piece_color);
    }

    bool is_king_attacked(const Board& board, const PieceColor piece_color) {
        const Position kingPos = piece_color == PieceColor::White
            ? board.state.white_king_pos
            : board.state.black_king_pos;

        return is_square_attacked(board, kingPos, piece_color);
    }

    bool is_move_legal(Board& board, const Position from_position, const Position to_position) {
        const Piece* piece_from = board.piece_at_position(from_position);
        const Piece* piece_to = board.piece_at_position(to_position);

        const bool is_en_passant = piece_from->get_kind() == PieceKind::Pawn
            && to_position.x != from_position.x
            && !piece_to;

        const bool is_castle = piece_from->get_kind() == PieceKind::King
            && std::abs(to_position.x - from_position.x) == 2;

        const Piece* capturedPiece = is_en_passant
            ? board.piece_at_position({to_position.x, from_position.y})
            : piece_to;

        const Move move {
            .move_string = "",
            .moved_piece = piece_from,
            .captured_piece = capturedPiece,
            .moved_from_position = from_position,
            .moved_to_position = to_position,
            .is_castle = is_castle,
            .is_en_passant = is_en_passant,
            .promotion_type = PieceKind::None,
            .previous_state = board.state
        };

        board.handle_move(move);

        const bool is_king_checked_after_move = is_king_attacked(board, piece_from->get_color());

        board.undo_move(move);

        return !is_king_checked_after_move;
    }

    void filter_legal_destinations(Board& board, const Position from, std::vector<Position>& pseudo_legal_to_positions) {
        std::erase_if(pseudo_legal_to_positions, [from, &board](const Position& pos) {
            return !is_move_legal(board, from, pos);
        });
    }

    bool has_legal_moves(Board& board, const PieceColor piece_color) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (const Piece* piece = board.grid[i][j];
                    piece && piece->get_color() == piece_color) {
                    std::vector<Position> positions = piece->generate_pseudo_legal_moves({j, i}, board);
                    filter_legal_destinations(board, {j, i}, positions);
                    if (!positions.empty()) return true;
                    }
            }
        }
        return false;
    }
}
