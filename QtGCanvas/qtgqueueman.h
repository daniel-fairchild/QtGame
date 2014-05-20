#ifndef QTGQUEUEMAN_H
#define QTGQUEUEMAN_H

#include "drawqueue.h"

class QtGQueueMan
{
public:
    QtGQueueMan(size_t qitem_size, int num_queues);

    ~QtGQueueMan();

    size_t frame_number();
    QtgDrawQueue* next_queue();

    void reset();

protected:
    size_t qitem_size;
    int num_queues;
    size_t frame_no;

    QtgDrawQueue** queues;
};

#endif // QTGQUEUEMAN_H
