#include "graphicsobserver.h"
#include "board.h"

GraphicsObserver::GraphicsObserver(Subject &sub) : subject(sub), xw(500, 500) {
    subject.attach(this);
}

GraphicsObserver::~GraphicsObserver() {
    subject.detach(this);
}

void GraphicsObserver::notify() {
    const Board &board = static_cast<const Board&>(subject.getState()); // idk if we need static cast, just to be safe though
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Square* square = board.getSquare(x, y);
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
