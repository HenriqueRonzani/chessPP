//
// Created by ronzani on 4/19/26.
//

#ifndef CCHESS_SCREEN_H
#define CCHESS_SCREEN_H
#include <map>

#include "raylib.h"
#include "chess/pieces/Piece.h"

class Screen {
    int screen_width;
    int screen_height;
    std::pmr::map<std::pair<PieceColor, PieceKind>, Texture2D> piece_textures;
    Texture2D get_piece_texture(PieceKind kind, PieceColor color);
    static void draw_square (int squareWidth, int squareHeight, int x_it, int y_it);
    void draw_piece (int squareWidth, int squareHeight, int x_it, int y_it, const Piece *piece) const;

public:
    Screen(int width, int height);
    ~Screen();

    void draw_board(const Piece *grid[8][8]) const;
};


#endif //CCHESS_SCREEN_H
