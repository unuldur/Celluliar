#ifndef SELECTIONMODE_H
#define SELECTIONMODE_H

#include "TreeUniverse.h"
#include "drawingmode.h"

#include <QRubberBand>
#include <functional>


class SelectionMode : public DrawingMode
{



public:
    enum SelectionType{ERASED, FULL, RANDOM, SELECTION};
    SelectionMode();
    SelectionMode(QWidget *qw, TreeUniverse *tu);
    void Press(QPoint pos, int sizeRect, QPoint offset);
    void Move(QPoint pos, int sizeRect, QPoint offset);
    void Release(QPoint pos, int sizeRect, QPoint offset);
    void UseSelection(SelectionType type, int sizeRect, QPoint offset);

private:
    QPoint origin;
    QRubberBand *rb;
    QWidget *qw;
    TreeUniverse *tu;
};

#endif // SELECTIONMODE_H
