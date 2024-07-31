#include <iostream>
#include <string>
#include <memory>
#include "controller.h"
#include "board.h"
#include "player.h"
#include "human.h"
#include "robot.h"

int main() {
    std::shared_ptr<Controller> controller = std::make_shared<Controller>();

    std::string command;
    std::cout << "> ";
    while (std::getline(std::cin, command)) {
        controller->handleCommand(command);
        std::cout << "> ";
    }
    std::cout << "End of game, thanks for playing! " << std::endl;
    controller->displayScore();
    return 0;
}
