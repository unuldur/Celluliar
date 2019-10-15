#include "utils.h"

Utils::Utils()
{

}

QPoint Utils::TruncPoint(const int sizeRect, const QPoint point)
{
    return QPoint((point.x() / sizeRect) * sizeRect, (point.y() / sizeRect) * sizeRect);
}
