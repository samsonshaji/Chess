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
    virtual std::vector<std::vector<std::shared_ptr<Square>>> getState() const = 0;
    virtual ~Subject() = 0;
};

#endif
