#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H

#include "observer.h"
#include "subject.h"
#include "window.h"

class GraphicsObserver : public Observer {
    Subject &subject;
    Xwindow xw;
public:
    GraphicsObserver(Subject &sub);
    ~GraphicsObserver();

    void notify() override;
};

#endif // GRAPHICSOBSERVER_H
