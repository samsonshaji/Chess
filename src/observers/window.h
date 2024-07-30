#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  int width, height;
  Font font;

 public:
  Xwindow(int width=1000, int height=1000);  
  ~Xwindow();                           
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};
  void fillRectangle(int x, int y, int width, int height, int colour=Black);
  void drawString(int x, int y, std::string msg, int colour=Black);
};

#endif
