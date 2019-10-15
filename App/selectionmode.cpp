#include "selectionmode.h"
#include "utils.h"

SelectionMode::SelectionMode()
{

}

SelectionMode::SelectionMode(QWidget *qw, TreeUniverse *tu):tu(tu)
{
    rb = new QRubberBand(QRubberBand::Rectangle, qw);
}

void SelectionMode::Press(QPoint pos, int sizeRect, QPoint offset)
{
    origin = Utils::TruncPoint(sizeRect, pos);
    rb->setGeometry(QRect(origin, QSize()));
    rb->show();
}

void SelectionMode::Move(QPoint pos, int sizeRect, QPoint offset)
{
     rb->setGeometry(QRect(origin, Utils::TruncPoint(sizeRect, pos) + QPoint(sizeRect, sizeRect)).normalized());
}

void SelectionMode::Release(QPoint pos, int sizeRect, QPoint offset)
{

}

void SelectionMode::UseSelection(SelectionMode::SelectionType type, int sizeRect, QPoint offset)
{
    std::function<int ()> choose;
    switch (type) {
        case FULL:
            choose = [](){return 1;};
            break;
        case ERASED:
            choose = [](){return 0;};
        break;
        case RANDOM:
            choose = [](){return rand() % 2;};
        break;
    }
    QPoint tOffset = Utils::TruncPoint(sizeRect, offset);
    for(int j = rb->pos().y(); j < rb->rect().height() + rb->pos().y() - sizeRect; j += sizeRect){
        for(int i = rb->pos().x(); i < rb->rect().width() + rb->pos().x() - sizeRect; i += sizeRect){
            tu->setByte(int((i + tOffset.x()) / sizeRect), int((j + tOffset.y()) / sizeRect), choose());
        }
    }
}
