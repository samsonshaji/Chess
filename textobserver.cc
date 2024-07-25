#include "textobserver.h"
#include <iostream>

TextObserver::TextObserver(Subject &s, int t, int b, int l, int r)
    : subject{s}, top{t}, bottom{b}, left{l}, right{r} {
    subject.attach(this);
}

TextObserver::~TextObserver() {
    subject.detach(this);
}

// same as render() from studio
void TextObserver::notify() {
    int cols = right-left+1;

    out << '+';
    for (int j = 0; j < cols; ++j) out << '-';
    out << '+' << std::endl;
    for (int i = top; i <= bottom; ++i) {
        out << '|';
        for (int j = left; j <= right; ++j) {
            out << subject.getState(i, j);
        }
        out << '|' << std::endl;
    }
    out << '+';
    for (int j = 0; j < cols; ++j) out << '-';
    out << '+' << std::endl;
}
