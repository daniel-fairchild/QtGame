#ifndef QTCTRLCOLLECTION_H
#define QTCTRLCOLLECTION_H

#include "qtgamepad.h"

class QtCtrlCollection
{
public:
    static QtCtrlCollection* factory(int num_mappings);

    QtCtrlCollection();
//    QtCtrlCollection(int num_mappings);

    virtual int numGamepads() = 0;
    virtual QtGamepad* gamepad(int index) = 0;

    /**
     * @brief update
     */
    virtual void probe_hardware() = 0;

protected:
    int num_mappings;

};

#endif // QTCTRLCOLLECTION_H
