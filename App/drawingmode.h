#ifndef DRAWINGMODE_H
#define DRAWINGMODE_H

#include <QPoint>



class DrawingMode
{
public:
    DrawingMode(){}
    virtual void Press(QPoint pos, int sizeRect, QPoint offset) = 0;
    virtual void Move(QPoint pos, int sizeRect, QPoint offset) = 0;
    virtual void Release(QPoint pos, int sizeRect, QPoint offset) = 0;
};

#endif // DRAWINGMODE_H
