#include <iostream>
#include <string>
#include "controller.h"
#include "board.h"
#include "player.h"
#include "human.h"
#include "robot.h"

int main() {
    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;

    Controller controller(whitePlayer, blackPlayer);

    std::string command;
    while(std::getline(std::cin, command)) {
        if (command == "game") {
            std::string whitePlayerType;
            std::string blackPlayerType;
            std::cin >> whitePlayerType >> blackPlayerType;

            if (whitePlayerType == "human") {
                whitePlayer = new Human(Colour::White);
            } else if (whitePlayerType == "computer1") {
                whitePlayer = new Robot(Colour::White, 1);
            } else if (whitePlayerType == "computer2") {
                whitePlayer = new Robot(Colour::White, 2);
            } else if (whitePlayerType == "computer3") {
                whitePlayer = new Robot(Colour::White, 3);
            }

            if (blackPlayerType == "human") {
                blackPlayer = new Human(Colour::Black);
            } else if (blackPlayerType == "computer1") {
                blackPlayer = new Robot(Colour::Black, 1);
            } else if (blackPlayerType == "computer2") {
                blackPlayer = new Robot(Colour::Black, 2);
            } else if (blackPlayerType == "computer3") {
                blackPlayer = new Robot(Colour::Black, 3);
            }

            controller.startGame(*whitePlayer, *blackPlayer);
        } else if (command == "resign") {
            controller.endGame(true);
        } else if (command == "move") {
            controller.runGame(*whitePlayer, *blackPlayer);
        } else if (command == "end") {
            break;
        }
    }
    return 0;
}