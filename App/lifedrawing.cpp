#include "drawmode.h"
#include "lifedrawing.h"
#include "selectionmode.h"
#include "utils.h"
#include <QMouseEvent>
#include <QPainter>
#include <QWheelEvent>
#include<iostream>

LifeDrawing::LifeDrawing(QWidget *parent) : QWidget(parent), sizeRect(10)
{

}

void LifeDrawing::setTreeUnivers(TreeUniverse * tu)
{
    this->tu = tu;
    dm = new DrawMode(tu, [](){return 1;});
}

void LifeDrawing::mousePressEvent(QMouseEvent *event)
{
       isPress = true;
       lastPosMouse = event->pos();
       dm->Press(lastPosMouse, sizeRect, offset);
}

void LifeDrawing::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && isPress){
        if(inAction) return;
        dm->Move(event->pos(), sizeRect, offset);
        update();
    }
    if ((event->buttons() & Qt::RightButton) && isPress){
        offset += lastPosMouse - event->pos();
        lastPosMouse = event->pos();
        update();
    }
}

void LifeDrawing::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isPress = false;
        if(inAction) return;
        dm->Release(lastPosMouse, sizeRect, offset);
        update();
    }
}


void LifeDrawing::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPoint tOffset = Utils::TruncPoint(sizeRect, offset);
    for(int j = 0; j < event->rect().height(); j += sizeRect){
        painter.drawLine(0, j, rect().width(), j);
    }
    for(int j = 0; j < event->rect().width(); j += sizeRect){
        painter.drawLine(j, 0, j, rect().height());
    }
    for(int j = 0; j < event->rect().height(); j += sizeRect){
        for(int i = 0; i < event->rect().width(); i += sizeRect){
            if(tu->getByte(int((i + tOffset.x()) / sizeRect), int((j + tOffset.y()) / sizeRect)) == 1){
                painter.fillRect(i, j, sizeRect, sizeRect, QColor("black"));
            }
        }
    }
}

void LifeDrawing::wheelEvent(QWheelEvent *event)
{
    sizeRect += event->angleDelta().y() > 0 ? 1 : -1;
    if(sizeRect > 10)
        sizeRect = 10;
    if(sizeRect < 1)
        sizeRect = 1;
    update();
}

void LifeDrawing::selectionUse(SelectionMode::SelectionType type)
{
    if(mode != Mode::SELECTION) return;
    dynamic_cast<SelectionMode*>(dm)->UseSelection(type, sizeRect, offset);
    update();
}

void LifeDrawing::changeMode(LifeDrawing::Mode mode)
{
    this->mode = mode;
    switch(mode){
    case Mode::BRUSH:
        dm = new DrawMode(tu, [](){return 1;});
        break;
    case Mode::ERASED:
        dm = new DrawMode(tu, [](){return 0;});
        break;
    case Mode::RANDOM:
        dm = new DrawMode(tu, [](){return rand() % 2;});
        break;
    case Mode::SELECTION:
        dm = new SelectionMode(this, tu);
        break;
    }
}

void LifeDrawing::setInAction(bool inAction)
{
    this->inAction = inAction;
}
