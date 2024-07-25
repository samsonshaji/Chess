#ifndef SQUARE_H
#define SQUARE_H

class Square {
public:
    int x;
    int y;

    Square(int x, int y);
    Square();

    bool isValid() const;
};

#endif // SQUARE_H
