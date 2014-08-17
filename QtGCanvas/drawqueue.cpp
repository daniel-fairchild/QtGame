#include <QDebug>
#include "qtgcanvas.h"
#include "qtgdrawer.h"

#define QPARTSIZEBITS 10
#define PMASK ((1 << QPARTSIZEBITS)-1)
#define QSUBQS 512

QtgDrawQueue::QtgDrawQueue(size_t item_size)
{
    this->item_size = item_size;
    this->sub_queues = (draw_base_t**)calloc(sizeof(draw_base_t*), QSUBQS);

    this->qpos = 0;
    this->part_mask = ((1 << QPARTSIZEBITS)-1);
    this->allocated_sub_queus = 0;
}

void QtgDrawQueue::lock()
{
    if (!this->mutex.tryLock()){
        qDebug() << "Drawqueue lock contention!";
        this->mutex.lock();
    }
}
void QtgDrawQueue::unlock()
{
    this->mutex.unlock();
}

draw_base_t* QtgDrawQueue::next_item(){
    this->next_lock.lock();
    // test to see if we need to grow the allocation size

    draw_base_t*  outp = _lookup(sub_queues, this->qpos++, this->item_size);
    this->next_lock.unlock();
    return  outp;
}

void QtgDrawQueue::draw_frame(){
    this->lock();
    for (int dp = 0 ; dp < qpos;){
        for (int cp = 0; dp < qpos  && cp <= PMASK ; cp++, dp++){
            draw_base_t* ti = _lookup(this->sub_queues, dp, this->item_size);
            ti->drawer->draw(ti);
        }
    }
    qpos = 0;
    this->unlock();
}

void QtgDrawQueue::add_sub_queue(size_t qnum)
{
    this->sub_queues[qnum] = (draw_base_t*)calloc(sizeof(draw_base_t), 1 << QPARTSIZEBITS);
    allocated_sub_queus++;
}

draw_base_t *QtgDrawQueue::_lookup(draw_base_t **queues, int qpos, size_t item_size){

    size_t sub_q = qpos >> QPARTSIZEBITS;

    if (sub_q >= this->allocated_sub_queus){
        this->add_sub_queue(sub_q);
    }

    draw_base_t* tbl = queues[sub_q];
    return (draw_base_t*) ((size_t)tbl + (PMASK & qpos)*item_size);
}
