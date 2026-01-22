//
// Created by ronzani on 1/18/26.
//

#ifndef CCHESS_MOVEHISTORY_H
#define CCHESS_MOVEHISTORY_H
#include <string>
#include <vector>
#include "../board/Position.h"
#include "../pieces/Piece.h"

class Piece;

struct Move {
    std::string moveText;
    Piece* movedPiece;
    Piece* capturedPiece = nullptr;
    Position from;
    Position to;

    Move();
};



class MoveHistory {
    std::vector<Move> history;

    public:
    MoveHistory();
};


#endif //CCHESS_MOVEHISTORY_H