#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <QQueue>
#include <QDebug>

template<class T>
class PriorityQueue {
public:
    PriorityQueue(){}
    void enqueue(int priority, T value){
        Item<T> item(priority, value);
        for(int i = 0; i < QUEUE.count(); i++) {
            const Item<T> &otherItem = QUEUE[i];
            if( priority > otherItem.PRIORITY )  {
                QUEUE.insert(i,item);
                return;
            }
        }
        QUEUE.append(item);
    }

    T dequeue(){
        const Item<T>& item = QUEUE.dequeue();
        return item.VALUE;
    }

    int count(){
        return QUEUE.count();
    }

    void update(int oldPriority, T value, int newPriority){
        PriorityQueue newQueue;
        for(int i = 0; i < count(); i++){
            const Item<T>& otherItem = QUEUE[i];
            if(otherItem.PRIORITY != oldPriority || otherItem.VALUE != value){
                newQueue.enqueue(otherItem.PRIORITY, otherItem.VALUE);
            }
        }
        newQueue.enqueue(newPriority, value);
        newQueue.QUEUE.swap(QUEUE);
    }

private:

    template<class C>
    struct Item{
        int PRIORITY;
        C VALUE;

        Item(int priority, C value){
            PRIORITY = priority;
            VALUE = value;
        }
    };

    QQueue<Item<T>> QUEUE;

};

#endif // PRIORITY_QUEUE_H
