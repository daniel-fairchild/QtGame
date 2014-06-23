#ifndef QTGAMEPAD_H
#define QTGAMEPAD_H


#include "ctrl_types.h"
#include <stdlib.h>


class QtGamepad
{

public:
    QtGamepad(size_t num_mappings);

//    static QtGamepad* factory(int num_mappings, int device_index);

    void update(size_t timestamp, int* outvals);
    void bind(CMAP_E from_type, CMAP_E to_type, unsigned char from, unsigned char to);
    void unbind(unsigned char target);

protected:
    gp_map_col_t* map;
    virtual int readButton(int btnindex) = 0;
    virtual int readAxis(int axisindex) = 0;
};



#endif // QTGAMEPAD_H
