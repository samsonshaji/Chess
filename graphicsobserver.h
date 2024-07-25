#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H

#include "observer.h"
#include "subject.h"
#include "window.h"

class GraphicsObserver : public Observer {
  // "has a" subject
  Subject &subject;
  int top, bottom, left, right;
  Xwindow xw;
public:
  // ctor
  GraphicsObserver(Subject &s, int t, int b, int l, int r);

  // dtor
  ~GraphicsObserver();

  // notify graphicsobserver
  void notify() override;
};

#endif
