#ifndef RUNTHREAD_H
#define RUNTHREAD_H
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "TreeUniverse.h"

class RunThread : public QThread
{

    Q_OBJECT

public:
    RunThread(QObject * parent, TreeUniverse * tu):QThread(parent), tu(tu), stop(false){}
    void setStop(bool s) {stop = s;}

public slots:
    void pause();
    void wakeUp();

protected:
    void run() override;


signals:
    void update();
private:
    TreeUniverse * tu;
    bool stop;
    QMutex mutex;
    QWaitCondition wait;
};

#endif // RUNTHREAD_H
