#ifndef QTGQUEUEMAN_H
#define QTGQUEUEMAN_H

#include "drawqueue.h"

class QtGQueueMan
{
public:
    QtGQueueMan(size_t qitem_size, int num_queues);

    ~QtGQueueMan();

    size_t frame_number();
    DrawQueue* next_queue();

protected:
    size_t qitem_size;
    int num_queues;
    size_t frame_no;

    DrawQueue** queues;
};

#endif // QTGQUEUEMAN_H
