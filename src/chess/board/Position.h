//
// Created by global on 22/01/2026.
//

#ifndef CCHESS_POSITION_H
#define CCHESS_POSITION_H

struct Position {
    int x, y;

    [[nodiscard]] bool isValid() const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    bool operator==(const Position& pos) const {
        return x == pos.x && y == pos.y;
    }

    bool operator!=(const Position& pos) const {
        return x != pos.x || y != pos.y;
    }
};

#endif //CCHESS_POSITION_H