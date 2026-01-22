
#include <iostream>

#include "src/chess/board/Board.h"

int main() {
    Board board;
    board.resetBoard();
    std::cout << board.toString();

    if (const auto piece = board.atPosition({0, 0})) {
        std::cout << "Peça encontrada: " << piece->toChar() << std::endl;
    } else {
        std::cout << "A casa está vazia!" << std::endl;
    }
    return 0;
}
