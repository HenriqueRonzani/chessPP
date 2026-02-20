
#include <format>
#include <iostream>
#include "src/chess/board/Board.h"

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

int main() {
    Board board;
    board.resetBoard();
    while (true) {

        clearScreen();
        std::cout << board.toString() << std::endl;
        std::cout << "Type 'quit' to exit" << std:: endl;

        try {
            std::string moveString;
            std::cin >> moveString;
            if (moveString == "quit") break;
            board.handleMove(moveString);
        } catch (std::invalid_argument& e) {
            std::cout << e.what() << std:: endl;
        }
    }
    return 0;
}

