//
// Created by ronzani on 1/17/26.
//

#include "Pawn.h"

#include "../helpers/BoardHelper.h"

std::vector<Position> Pawn::generate_pseudo_legal_moves(const Position pos, const Board& board) const {
    const int move_directions = color == PieceColor::White ? 1 : -1;
    const int starting_row = color == PieceColor::White ? 1 : 6;

    std::vector<Position> possibleMoves;

    const Position forward_position = { pos.x, pos.y + move_directions };
    if (forward_position.is_valid() && chess::rules::is_square_free(board, forward_position)) {
        possibleMoves.push_back(forward_position);

        const Position double_forward_position = { pos.x, pos.y + move_directions * 2 };
        if (pos.y == starting_row && double_forward_position.is_valid() && chess::rules::is_square_free(board, double_forward_position)) {
            possibleMoves.push_back(double_forward_position);
        }
    }

    for (const int xShift : { 1, -1 }) {
        const Position capture_position = { pos.x + xShift, pos.y + move_directions};
        if (capture_position.is_valid()) {
            const Piece* pieceAtPosition = board.piece_at_position(capture_position);
            if (pieceAtPosition != nullptr && pieceAtPosition->is_enemy(this)) {
                possibleMoves.push_back(capture_position);
            }
        }
    }

    if (const auto en_passant_target = board.state.en_passant_target;
        en_passant_target &&
        en_passant_target->is_adjacent(pos)
    ) {
        possibleMoves.push_back({en_passant_target.value().x, pos.y + move_directions});
    }

    return possibleMoves;
}
