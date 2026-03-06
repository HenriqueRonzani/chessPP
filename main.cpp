
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
        const PieceColor color = board.history.getNextMoveColor();

        clearScreen();
        if (!board.hasLegalMoves(color)) {
            std::cout << "The game has ended. ";
            if (board.isKingAttacked(color))
                std::cout << PieceTypeHelper::getColorName(color) << " has lost by checkmate";
            else
                std::cout << " has been stalemated, it's a draw";
            std::cout << std::endl;
            break;
        }

        std::cout << "Next to play: " << PieceTypeHelper::getColorName(color) << std::endl;
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
