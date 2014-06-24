#ifndef QTGAMEPAD_H
#define QTGAMEPAD_H


#include "ctrl_types.h"
#include <stdlib.h>


class QtGamepad
{

public:
    QtGamepad(size_t num_mappings);

    /**
     * @brief update
     * @param timestamp
     * @param outvals
     *      Button protocol:
     *      0:    button not held
     *      x<0:  button pressed, held for x timesteps
     *      x>0:  button released this frame after having been held for x timesteps
     */
    void read_mappings(size_t timestamp, int* outvals);
    void reset();

    void bind(CMAP_E from_type, CMAP_E to_type, unsigned char from, unsigned char to);
    void unbind(unsigned char target);

    virtual int numButtons() = 0;
    virtual int numAxes() = 0;

protected:
    gp_map_col_t* map;
    virtual int readButton(int btnindex) = 0;
    virtual int readAxis(int axisindex) = 0;
};



#endif // QTGAMEPAD_H
