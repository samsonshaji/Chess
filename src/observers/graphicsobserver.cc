#include "graphicsobserver.h"
#include "board.h"

GraphicsObserver::GraphicsObserver(Subject &sub) : subject(sub), xw(500, 500) {
    subject.attach(this);
}

GraphicsObserver::~GraphicsObserver() {
    subject.detach(this);
}

void GraphicsObserver::notify() {
    std::vector<std::vector<Square*>> board = subject.getState();

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Square* square = board[x][y];
            if (square->getPiece()) {
                char pieceSymbol = square->getPiece()->getSymbol();
                std::string pieceSymbolStr(1, pieceSymbol);
                xw.drawString(x * 60, y * 60, pieceSymbolStr);
            } else {
                xw.drawString(x * 60, y * 60, "_");
            }
        }
    }
}
