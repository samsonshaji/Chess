#include "subject.h"
#include "observer.h"
#include <algorithm>

void Subject::attach(Observer *o) {
  observers.push_back(o);
}

void Subject::detach(Observer *o) {
  observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Subject::notifyObservers() {
  for (auto &obs : observers) {
    obs->notify();
  }
}
