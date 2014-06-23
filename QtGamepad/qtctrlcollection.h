#ifndef QTCTRLCOLLECTION_H
#define QTCTRLCOLLECTION_H

#include "qtgamepad.h"

class QtCtrlCollection
{
public:
    QtCtrlCollection();
    QtCtrlCollection(int num_mappings);

    int numGamepads();

    /*    bool assign(QtGamepad* gp);
    bool release(QtGamepad* gp);*/

protected:
    int num_mappings;

private:
    QtCtrlCollection* actual;
};

#endif // QTCTRLCOLLECTION_H
