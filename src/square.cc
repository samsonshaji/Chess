#include "square.h"

Square::Square() : piece(PieceType::Empty), color(Color::White) {}

Square::Square(PieceType p, Color c) : piece(p), color(c) {}

PieceType Square::getPiece() const {
    return piece;
}

Color Square::getColor() const {
    return color;
}

void Square::setPiece(PieceType p) {
    piece = p;
}

void Square::setColor(Color c) {
    color = c;
}

void Square::attach(Observer *o) {
    observers.push_back(o);
}

void Square::detach(Observer *o) {
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Square::notifyObservers() {
    for (auto &o : observers) {
        o->notify();
    }
}

void Square::setSquare(Piece *newPiece, Color newColor) {
    piece = newPiece->getType();
    color = newColor;
    notifyObservers();
}

std::ostream &operator<<(std::ostream &out, const Square &s) {
    out << s.piece;
    return out;
}
