//
// Created by ronzani on 1/17/26.
//

#ifndef CCHESS_BOARD_H
#define CCHESS_BOARD_H
#include "../pieces/Piece.h"


class Board {
    Piece* grid[8][8];
public:
    void resetBoard();
    Board();
};


#endif //CCHESS_BOARD_H