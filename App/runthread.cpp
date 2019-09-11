#include "runthread.h"


void RunThread::pause()
{
    stop = true;
}

void RunThread::wakeUp()
{
    mutex.lock();
    wait.wakeAll();
    mutex.unlock();
}

void RunThread::run() {
    mutex.lock();
    wait.wait(&mutex);
    mutex.unlock();
    while(true) {
        mutex.lock();
        if(stop){
            wait.wait(&mutex);
            stop = false;
        }
        mutex.unlock();
        tu->runStep();
        QThread::msleep(100);
        emit update();
    }
}
