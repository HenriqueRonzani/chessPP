//
// Created by ronzani on 19/03/2026.
//

#ifndef CCHESS_RULEVALIDATOR_H
#define CCHESS_RULEVALIDATOR_H
#include <vector>

#include "../board/Board.h"
#include "../board/Position.h"
#include "../pieces/PieceTypes.h"

namespace chess::rules {
    struct CastleRookPositions {
        Position origin;
        Position destination;
    };

    CastleRookPositions get_rook_castle_positions(const Move& move);

    bool scan_for_attackers(const Board& board, Position pos, PieceColor piece_color, const std::vector<Position> &move_directions, std::initializer_list<PieceKind> kinds,
    int max_steps = 8);

    void filter_legal_destinations(Board& board, Position from, std::vector<Position>& pseudo_legal_to_positions);

    bool is_square_attacked(const Board& board, const Position& pos, PieceColor piece_color);
    bool is_square_free(const Board&, const Position& pos);
    bool is_square_free_and_not_attacked(const Board& board, const Position& pos, PieceColor piece_color);

    bool is_king_attacked(const Board&, PieceColor piece_color);
    bool is_move_legal(Board&, Position from_position, Position to_position);
    bool has_legal_moves(Board&, PieceColor piece_color);
    Position find_moveable_to_target(Position target, PieceKind kind, PieceColor color, int piece_column = -1, int piece_row = -1) const;
};


#endif //CCHESS_RULEVALIDATOR_H