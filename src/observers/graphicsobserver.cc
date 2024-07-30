#include "graphicsobserver.h"
#include "board.h"
#include <string>
#include <sstream>

GraphicsObserver::GraphicsObserver(Subject &sub) : subject(sub), win(1000, 1000) {
    subject.attach(this);
}

GraphicsObserver::~GraphicsObserver() {
    subject.detach(this);
}

void GraphicsObserver::notify() {
    if(!gridDrawn){
        win.fillRectangle(0, 0, 1000, 1000, Xwindow::Black);

        for(int i = 0; i < 2; i++){
            win.drawString(100*1 + 50, 50 + (900 * i), "A", Xwindow::White);
            win.drawString(100*2 + 50, 50 + (900 * i), "B", Xwindow::White);
            win.drawString(100*3 + 50, 50 + (900 * i), "C", Xwindow::White);
            win.drawString(100*4 + 50, 50 + (900 * i), "D", Xwindow::White);
            win.drawString(100*5 + 50, 50 + (900 * i), "E", Xwindow::White);
            win.drawString(100*6 + 50, 50 + (900 * i), "F", Xwindow::White);
            win.drawString(100*7 + 50, 50 + (900 * i), "G", Xwindow::White);
            win.drawString(100*8 + 50, 50 + (900 * i), "H", Xwindow::White);

            win.drawString(50 + (900 * i), 100*9 - 50, "1", Xwindow::White);
            win.drawString(50 + (900 * i), 100*8 - 50, "2", Xwindow::White);
            win.drawString(50 + (900 * i), 100*7 - 50, "3", Xwindow::White);
            win.drawString(50 + (900 * i), 100*6 - 50, "4", Xwindow::White);
            win.drawString(50 + (900 * i), 100*5 - 50, "5", Xwindow::White);
            win.drawString(50 + (900 * i), 100*4 - 50, "6", Xwindow::White);
            win.drawString(50 + (900 * i), 100*3 - 50, "7", Xwindow::White);
            win.drawString(50 + (900 * i), 100*2 - 50, "8", Xwindow::White); 
        }
        gridDrawn = true;
    }   

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                win.fillRectangle(100*(j + 1), 100*(8-i), 100, 100, Xwindow::Brown);
            } else {
                win.fillRectangle(100*(j + 1), 100*(8-i), 100, 100, Xwindow::White);
            }

            std::vector<std::vector<Square*>> board = subject.getState();

            char piece;
            if(board[i][j]->getPiece() == nullptr){
                piece = '_';
            } else {
                piece = board[i][j]->getPiece()->getSymbol();
            }
            
            if(piece != ' ' && piece != '_'){ 
                std::stringstream ss;
                std::string s;
                ss << piece;
                ss >> s;
            
                if(piece + 0 > 96){
                    win.drawString(100*(j + 1) + 50, 100*(9-i) - 50, s, Xwindow::Black);
                } else {
                    win.drawString(100*(j + 1) + 50, 100*(9-i) - 50, s, Xwindow::Black);
                }  
            }
        }
    }
}
