//
// Created by ronzani on 1/18/26.
//

#include "King.h"

#include "../helpers/BoardHelper.h"

std::vector<Position> King::generate_pseudo_legal_moves(const Position pos, const Board &board) const {
    static const std::vector<Position> king_move_directions = {
        {1, -1}, {-1, 1}, {1, 1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    std::vector<Position> moves = generate_sliding_moves(pos, board, king_move_directions, 1);

    const PieceColor king_color = board.piece_at_position(pos)->get_color();

    if (!chess::rules::is_king_attacked(board, king_color)) {

        if (board.can_castle(CastleDirection::KingSide, king_color)) {
            if (chess::rules::is_square_free_and_not_attacked(board, {pos.x + 1, pos.y}, king_color) &&
                chess::rules::is_square_free_and_not_attacked(board, {pos.x + 2, pos.y}, king_color)
                )
                moves.push_back({pos.x + 2, pos.y});
        }

        if (board.can_castle(CastleDirection::QueenSide, king_color)) {
            if (chess::rules::is_square_free_and_not_attacked(board, {pos.x - 1, pos.y}, king_color) &&
                chess::rules::is_square_free_and_not_attacked(board, {pos.x - 2, pos.y}, king_color) &&
                board.piece_at_position({pos.x - 3, pos.y}) == nullptr
                )
                moves.push_back({pos.x - 2, pos.y});
        }
    }
    return moves;
}
