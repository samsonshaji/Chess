#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H

#include "observer.h"
#include "subject.h"
#include "window.h"

class GraphicsObserver : public Observer {
    Subject &subject;
    Xwindow win;
    bool gridDrawn = false;
public:
    GraphicsObserver(Subject &sub);
    ~GraphicsObserver();

    void notify() override;
};

#endif 
