#ifndef DRAWMODE_H
#define DRAWMODE_H

#include "TreeUniverse.h"
#include "drawingmode.h"

#include <QRect>
#include <functional>


class DrawMode : public DrawingMode
{
public:
    DrawMode();
    DrawMode(TreeUniverse *tu, std::function<int ()> choose);

    // DrawingMode interface
public:
    void Press(QPoint pos,int sizeRect, QPoint offset);
    void Move(QPoint pos,int sizeRect, QPoint offset);
    void Release(QPoint pos,int sizeRect, QPoint offset);

private:
    std::function<int ()> choose;
    TreeUniverse *tu;
    QPoint lastPosMouse;
    QRect lastRect;
    void setPoint(QPoint point, int sizeRect, QPoint offset);
};

#endif // DRAWMODE_H
