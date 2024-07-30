#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

Xwindow::Xwindow(int width, int height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        std::cerr << "Cannot open display" << std::endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0, (XGCValues *)0);

    XFlush(d);

    // Set up colours.
    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10] = {"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

    cmap = DefaultColormap(d, DefaultScreen(d));
    for (int i = 0; i < 10; ++i) {
        XParseColor(d, cmap, color_vals[i], &xcolour);
        XAllocColor(d, cmap, &xcolour);
        colours[i] = xcolour.pixel;
    }

    XSetForeground(d, gc, colours[Black]);

    // Load the bold font
    Font font = XLoadFont(d, "-adobe-courier-bold-r-normal--34-240-100-100-m-200-iso8859-1");
    XSetFont(d, gc, font);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d, True);

    usleep(1000);

    // Make sure we don't race against the Window being shown
    XEvent ev;
    while (1) {
        XNextEvent(d, &ev);
        if (ev.type == Expose) break;
    }
}

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XUnloadFont(d, font);
    XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, std::string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XSetForeground(d, gc, colours[Black]);
}

// void Xwindow::drawChessboard() {
//     int squareSize = 100; // size of each square on the chessboard
//     bool isWhite = true; // start with a white square
//     for (int i = 0; i < 8; ++i) {
//         for (int j = 0; j < 8; j++) {
//             int color = isWhite ? White : Black; // 0 for white, 1 for black
//             fillRectangle(j * squareSize, i * squareSize, squareSize, squareSize, color);
//             isWhite = !isWhite; // alternate colors
//         }
//         isWhite = !isWhite; // alternate starting color for next row
//     }
// }