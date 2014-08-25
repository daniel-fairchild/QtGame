#ifndef QTSDLCTRLCOLLECTION_H
#define QTSDLCTRLCOLLECTION_H

//#include <SDL/SDL.h>

#include "../qtctrlcollection.h"
#include "gamepad.h"

class QtSDLCtrlCollection  : public QtCtrlCollection
{
public:
    QtSDLCtrlCollection(int num_mappings);

    // QtCtrlCollection interface
public:
    int numGamepads();
    QtGamepad* gamepad(int index);
    void probe_hardware();


private:
    QtGamepad* gamepads[17];

};

#endif // QTSDLCTRLCOLLECTION_H
