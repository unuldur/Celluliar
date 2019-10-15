#ifndef LIFEDRAWING_H
#define LIFEDRAWING_H

#include <QWidget>
#include <QVector2D>
#include <QRubberBand>
#include "TreeUniverse.h"
#include "drawingmode.h"
#include "selectionmode.h"

class LifeDrawing : public QWidget
{
    Q_OBJECT
public:
    enum Mode{ERASED, BRUSH, RANDOM, SELECTION};

    explicit LifeDrawing(QWidget *parent = nullptr);
    void setTreeUnivers(TreeUniverse*);
    void changeMode(Mode mode);
    void setInAction(bool inAction);
    void selectionUse(SelectionMode::SelectionType type);
signals:

public slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    bool isPress;
    bool inAction = false;
    QPoint offset = QPoint(0, 0);
    QPoint lastPosMouse;
    int sizeRect = 10;
    Mode mode = Mode::BRUSH;
    TreeUniverse* tu;
    DrawingMode* dm;


    void drawRect(QPoint point);
};

#endif // LIFEDRAWING_H
