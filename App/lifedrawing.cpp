#include "lifedrawing.h"
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
}

void LifeDrawing::mousePressEvent(QMouseEvent *event)
{
       isPress = true;
       lastPosMouse = event->pos();
}

void LifeDrawing::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && isPress){
        setPoint(event->pos());
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
        setPoint(event->pos());
    }
}


void LifeDrawing::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPoint tOffset = TruncOffset();

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

void LifeDrawing::changeMode(LifeDrawing::Mode mode)
{
    this->mode = mode;
}

void LifeDrawing::setInAction(bool inAction)
{
    this->inAction = inAction;
}

void LifeDrawing::setPoint(QPoint point)
{
    if(inAction) return;
    QPoint posReal = QPoint((point.x()/sizeRect) * sizeRect, (point.y()/sizeRect) * sizeRect);

    QRect rect = QRect(posReal, posReal + QPoint(sizeRect, sizeRect));
    if(lastRect == rect) return;
    lastRect = rect;

    QPoint truncOffset = TruncOffset();
    QPoint posLife = QPoint((point.x() + truncOffset.x())/sizeRect, (point.y() + truncOffset.y())/sizeRect);
    bool live = true;
    switch(mode){
        case Mode::BRUSH: live = true; break;
        case Mode::ERASED: live = false; break;
        case Mode::RANDOM: live = rand() % 2 == 1 ? true : false; break;
    }
    tu->setByte(posLife.x(), posLife.y(), live);


    update();
}

QPoint LifeDrawing::TruncOffset()
{
    return QPoint((offset.x() / sizeRect) * sizeRect, (offset.y() / sizeRect) * sizeRect);
}
