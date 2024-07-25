#include "graphicsobserver.h"

// initialize xw via MIL
// width = (r-l+1)*10
// height = (b-t+1)* 10
GraphicsObserver::GraphicsObserver(Subject &s, int t, int b, int l, int r)
    : subject{s}, top{t}, bottom{b}, left{l}, right{r}, xw{10*(r-l+1), 10*(b-t+1)} {
    subject.attach(this);
}

GraphicsObserver::~GraphicsObserver() {
    subject.detach(this);
}

void GraphicsObserver::notify() {
    for (int i = top; i <= bottom; ++i) {
        for (int j = left; j <= right; ++j) {

            // get state from subject to render
            char currchar = subject.getState(i, j);

            // compute graphics color
            int color;
            if ('a' <= currchar && currchar <= 'z') color = Xwindow::Red;
            else if ('A' <= currchar && currchar <= 'Z') color = Xwindow::Green;
            else if ('0' <= currchar && currchar <= '9') color = Xwindow::Blue;
            else if (currchar != ' ') color = Xwindow::Black;
            else color = Xwindow::White;

            // fill
            int width = 10*(j-left);
            int height = 10*(i-top);
            xw.fillRectangle(width, height, 10, 10, color);
        }
    }
}
