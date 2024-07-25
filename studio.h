#ifndef STUDIO_H
#define STUDIO_H

#include "subject.h"
#include <iostream>
class AsciiArt;

// inherits from subject
class Studio : public Subject {
  int rows=10, cols=10, ticks = 0;
  std::ostream &out = std::cout;

  AsciiArt *thePicture;

 public:
  explicit Studio(AsciiArt *picture): thePicture{picture} {}

  AsciiArt *&picture() { return thePicture; }
  void reset();
  void render();
  void animate(int numTicks);

  // getState added
  char getState(int row, int col) const override;
  ~Studio();
};

#endif
