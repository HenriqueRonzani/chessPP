//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_BOARD_H
#define CCHESS_BOARD_H
#include "Position.h"
#include <string>
#include "../move/MoveHistory.h"
#include "../pieces/Piece.h"

class Piece;

struct CastleRookPositions {
    Position origin;
    Position destination;
};

class Board {
    Piece* grid[8][8];

    Position white_king_pos = white_king_start;
    Position black_king_pos = black_king_start;


    static CastleRookPositions get_castle_simulation_context(Piece *king, Position king_origin, Position king_destination);
    void simulate_move(Position origin, Position destination, Piece *piece_moving_to_destination, Piece *piece_moving_to_origin, bool is_en_passant, Piece *
                       piece_at_en_passant_position, bool is_castle, Position castle_rook_origin, Position castle_rook_destination, Position king_position);
    void undo_move_simulation(Piece *piece_at_origin, Position origin, Position destination, bool is_en_passant, Piece *en_passant_victim, bool
                              is_castle, CastleRookPositions rook_positions, Position current_king_position);

    void handle_castle(const Move& move);
    void move_piece(Position from, Position to);

    [[nodiscard]] bool scan_for_attackers(Position pos, PieceColor piece_color, const std::vector<Position> &move_directions, std::initializer_list<PieceKind> kinds,
        int max_steps = 8) const;
    void filter_legal_destinations(Position from, std::vector<Position>& pseudo_legal_to_positions);

public:
    static constexpr Position white_king_start = { 4, 0 };
    static constexpr Position black_king_start = { 4, 7 };

    Board();
    MoveHistory history;
    void reset_board();
    void handle_move(const Move &move, PieceColor moving_color);
    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] Piece* piece_at_position(Position position) const;
    [[nodiscard]] Position find_moveable_to_target(Position target, PieceKind kind, PieceColor color, int piece_column = -1, int piece_row = -1) const;

    [[nodiscard]] bool is_square_attacked(const Position& pos, PieceColor piece_color) const;
    [[nodiscard]] bool is_square_free(const Position& pos) const;
    [[nodiscard]] bool is_square_free_and_not_attacked(const Position& pos, PieceColor piece_color) const;

    [[nodiscard]] bool is_king_attacked(PieceColor piece_color) const;
    bool is_move_legal(Position from_position, Position to_position);
    [[nodiscard]] bool has_legal_moves(PieceColor piece_color);
};


#endif //CCHESS_BOARD_H