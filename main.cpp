
#include <format>
#include <iostream>

#include "src/chess/board/Board.h"

int main() {
    Board board;
    board.resetBoard();
    std::cout << board.toString();
    return 0;
}
