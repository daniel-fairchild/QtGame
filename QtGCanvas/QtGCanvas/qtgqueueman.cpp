#include "../qtgqueueman.h"

QtGQueueMan::QtGQueueMan(size_t qitem_size, int num_queues)
{
    this->qitem_size = qitem_size;
    this->num_queues = num_queues;

    this->queues = (QtgDrawQueue**)calloc(sizeof(QtgDrawQueue**), num_queues);
    for (int i = 0; i < num_queues; i++){
        queues[i] = new QtgDrawQueue(this->qitem_size);
//        queues[i]->lock();

    }
    this->frame_no = 0;
}

QtGQueueMan::~QtGQueueMan(){
    for (int i = 0; i < num_queues; i++){
        queues[i]->lock();
        queues[i]->unlock();
        delete queues[i];
    }
    free(this->queues);
}

size_t QtGQueueMan::frame_number()
{
    return this->frame_no;
}

QtgDrawQueue *QtGQueueMan::next_queue()
{
    QtgDrawQueue* outp = queues[this->frame_no % this->num_queues];
    outp->lock();
    this->frame_no++;
    outp->unlock();
    return outp;
}

void QtGQueueMan::reset()
{
    for (int i = 0; i < this->num_queues; i++){
        this->queues[i]->lock();
    }
    this->frame_no = 0;
    for (int i = 0; i < this->num_queues; i++){
        this->queues[i]->unlock();
    }
}
