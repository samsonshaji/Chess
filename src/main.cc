#include <iostream>
#include <string>
#include "controller.h"
#include "player.h"
// #include "robot.h"

int main() {
    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;

    //create main controller, this will control the game flow through user input
    Controller controller(whitePlayer, blackPlayer);

    cout << "Welcome to Chess! " << endl;

    //main game command loop
    std::string command;
    std::cout << "> ";
    while (std::getline(std::cin, command)) {
        controller.handleCommand(command);
        std::cout << "> ";
    }
    std::cout << "End of game, thanks for playing! " << std::endl;
    controller.displayScore();
    return 0;
}
