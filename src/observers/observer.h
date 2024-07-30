#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "board.h"

class Subject;

class Observer {
  public:
    Board *board;
    virtual void notify() = 0;
    virtual ~Observer() = 0;
};
#endif
