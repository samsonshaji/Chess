#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include <iostream>

#include "observer.h"
#include "subject.h"

class TextObserver : public Observer {
    std::ostream &out;
    Subject &subject;
public:
    TextObserver(Subject &sub, std::ostream &out = std::cout);
    ~TextObserver();

    void notify() override;
};

#endif
