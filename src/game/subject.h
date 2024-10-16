#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <iostream>

#include "square.h"

class Observer;

class Subject {
    std::vector<Observer*> observers;
  public:
    void attach(Observer *o);
    void detach(Observer *o);
    void notifyObservers();
    // getState returns the current state of the board
    virtual std::vector<std::vector<Square*>> getState() const = 0;
    virtual ~Subject() = 0;
};

#endif
