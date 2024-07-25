#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include <iostream>

#include "observer.h"
#include "subject.h"

class TextObserver : public Observer {
  std::ostream &out = std::cout;
  // "has a" subject
  Subject &subject;
  int top, bottom, left, right;
public:
  // ctor
  TextObserver(Subject &s, int t, int b, int l, int r);

  // dtor
  ~TextObserver();

  // notify textobserver
  void notify() override;
};

#endif
