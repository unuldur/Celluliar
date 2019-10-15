#include "drawmode.h"
#include "utils.h"

DrawMode::DrawMode():DrawingMode()
{

}

DrawMode::DrawMode(TreeUniverse *tu, std::function<int ()> choose):DrawingMode(), choose(choose), tu(tu)
{

}

void DrawMode::Press(QPoint pos,int sizeRect, QPoint offset)
{
    lastPosMouse = pos;
}

void DrawMode::Move(QPoint pos,int sizeRect, QPoint offset)
{
    setPoint(pos, sizeRect, offset);
}

void DrawMode::Release(QPoint pos,int sizeRect, QPoint offset)
{
    setPoint(pos, sizeRect, offset);
}

void DrawMode::setPoint(QPoint point, int sizeRect, QPoint offset)
{
    QPoint posReal = Utils::TruncPoint(sizeRect, point);

    QRect rect = QRect(posReal, posReal + QPoint(sizeRect, sizeRect));

    if(lastRect == rect) return;
    lastRect = rect;

    QPoint truncOffset = Utils::TruncPoint(sizeRect, offset);
    QPoint posLife = QPoint((point.x() + truncOffset.x())/sizeRect, (point.y() + truncOffset.y())/sizeRect);
    tu->setByte(posLife.x(), posLife.y(), choose());

}

