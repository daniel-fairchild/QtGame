#include "../qtgqueueman.h"

QtGQueueMan::QtGQueueMan(size_t qitem_size, int num_queues)
{
    this->qitem_size = qitem_size;
    this->num_queues = num_queues;

    this->queues = (DrawQueue**)calloc(sizeof(DrawQueue**), num_queues);
    for (int i = 0; i < num_queues; i++){
        queues[i] = new DrawQueue(this->qitem_size);
//        queues[i]->lock();
    }
}

QtGQueueMan::~QtGQueueMan(){
    for (int i = 0; i < num_queues; i++){
        queues[i]->lock();
        queues[i]->unlock();
        delete queues[i];
    }
    free(this->queues);
}

DrawQueue *QtGQueueMan::next_queue()
{
    DrawQueue* outp = queues[this->frame_no & this->num_queues];
    outp->lock();
    this->frame_no++;
    outp->unlock();
    return outp;
}
