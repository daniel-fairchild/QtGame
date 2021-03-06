#ifndef DRAWQUEUE_H
#define DRAWQUEUE_H

#include <QObject>
#include <QVector>
#include <QMutex>


#include "draw_base_t.h"

class QtgDrawQueue
{
public:
    explicit QtgDrawQueue(size_t item_size);

    /**
     * @brief aquire exclusive access to this queue
     */
    void lock();

    /**
     * @brief release exclusive access to this queue
     */
    void unlock();

    /**
     * @brief Add a DrawAble object to this queue
     * @param What is to be drawn as part of this queue
     */
    draw_base_t* next_item();

    /**
     * @brief Executes draw() on all drawables in queue and empties it.
     */
    void draw_frame();

private:
    QMutex mutex;
    QMutex next_lock;
    draw_base_t** sub_queues;
    int qpos;
    unsigned int part_mask;
    size_t allocated_sub_queus;

    void add_sub_queue(size_t qnum);

    draw_base_t* _lookup(draw_base_t** queues, int qpos, size_t item_size);

    size_t item_size;
};

#endif // DRAWQUEUE_H
