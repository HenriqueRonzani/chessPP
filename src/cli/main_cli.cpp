#include <iostream>

#include "../chess/Engine.h"
#include "../chess/board/Board.h"

int main() {
    Engine engine;
    while (true) {
        const std::string color_name = engine.get_moving_color_name();

        std::cout << engine.get_board_to_string() << std::endl;

        if (engine.is_game_over_by_checkmate_or_stalemate()) {
            std::cout << "The game has ended. ";
            if (engine.is_king_attacked())
                std::cout << color_name << " has lost by checkmate";
            else
                std::cout << " has been stalemated, it's a draw";
            std::cout << std::endl;
            break;
        }
        if (engine.is_game_over_by_fifty_move_rule()) {
            std::cout << "The game has ended. Fifty move rule, it's a draw";
            break;
        }
        std::cout << "Next to play: " << color_name << std::endl;

        std::cout << "Type 'quit' to exit" << std::endl;

        try {
            std::string move_string;
            std::cin >> move_string;
            if (move_string == "quit") break;
            if (move_string == "undo") {
                engine.undo_move();
            }
            else {
                engine.make_move(move_string);
            }
        } catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
