//
// Created by ronzani on 4/19/26.
//

#include "Screen.h"

#include <ranges>

#include "raylib.h"
#include "chess/helpers/PieceHelper.h"
#include "chess/pieces/Piece.h"

void Screen::draw_square(const int squareWidth, const int squareHeight, const int x_it, const int y_it) {
    const int positionX = x_it * squareWidth;
    const int positionY = y_it * squareHeight;
    const Color square_color = (x_it + y_it) % 2 == 0 ? BEIGE : BROWN;
    DrawRectangle(positionX, positionY, squareWidth, squareHeight, square_color);
}

void Screen::draw_piece(const int squareWidth, const int squareHeight, const int x_it, const int y_it,
                        const Piece *piece) const {
    const Texture2D piece_texture = piece_textures.at({piece->get_color(), piece->get_kind()});
    const auto scale = static_cast<float>(squareWidth / 4.0 * 3 / piece_texture.width);

    const float x_pos = static_cast<float>(x_it) * static_cast<float>(squareWidth) + static_cast<float>(squareWidth) / 2
                        - static_cast<float>(piece_texture.width) * scale / 2;
    const float y_pos = static_cast<float>(y_it) * static_cast<float>(squareHeight) + static_cast<float>(squareHeight) /
                        2 - static_cast<float>(piece_texture.height) * scale / 2;

    // x y
    // y.a = x/2
    // a = x/2y
    DrawTextureEx(
        piece_texture,
        {x_pos, y_pos},
        0,
        scale,
        WHITE
    );
}

void Screen::draw_board(const Piece *grid[8][8]) const {
    const int squareWidth = screen_width / 8;
    const int squareHeight = screen_height / 8;

    ClearBackground(WHITE);
    BeginDrawing();
    for (int x_it = 0; x_it < 8; x_it++) {
        for (int y_it = 0; y_it < 8; y_it++) {
            draw_square(squareWidth, squareHeight, x_it, y_it);
            if (grid[7-y_it][7-x_it]) {
                draw_piece(squareWidth, squareHeight, x_it, y_it, grid[7-y_it][7-x_it]);
            }
        }
    }
    EndDrawing();
}

Screen::~Screen() {
    for (const auto &textura: piece_textures | std::views::values) {
        UnloadTexture(textura);
    }
}

Screen::Screen(const int width, const int height) : screen_width(width), screen_height(height) {
    InitWindow(screen_width, screen_height, "Cchess GUI");
    SetTargetFPS(60);

    constexpr PieceColor colors[] = {PieceColor::White, PieceColor::Black};
    constexpr PieceKind kinds[6] = {
        PieceKind::King, PieceKind::Queen, PieceKind::Rook,
        PieceKind::Knight, PieceKind::Bishop, PieceKind::Pawn
    };

    for (const PieceColor color: colors) {
        for (const PieceKind kind: kinds) {
            const std::string path = "../assets/" +
                                     chess::piece_helper::get_color_name(color) +
                                     "-" +
                                     chess::piece_helper::get_kind_name(kind) +
                                     ".png";
            const Texture2D texture = LoadTexture(path.c_str());
            piece_textures[{color, kind}] = texture;
        }
    }
}

Texture2D Screen::get_piece_texture(const PieceKind kind, const PieceColor color) {
    return piece_textures[{color, kind}];
}
