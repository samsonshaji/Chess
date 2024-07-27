#include "textobserver.h"
#include "board.h"

TextObserver::TextObserver(Subject &sub, std::ostream &out) : subject(sub), out(out) {
    subject.attach(this);
}

TextObserver::~TextObserver() {
    subject.detach(this);
}

void TextObserver::notify() {
    std::vector<std::vector<Square*>> board = subject.getState();
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Square* square = board[x][y];
            if (square->getPiece()) {
                out << square->getPiece()->getSymbol() << ' ';
            } else {
                out << "_ ";
            }
        }
        out << std::endl;
    }
}
