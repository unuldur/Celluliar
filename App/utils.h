#ifndef UTILS_H
#define UTILS_H

#include <QPoint>



class Utils
{
public:
    Utils();
    static QPoint TruncPoint(const int sizeRect,const QPoint offset);
};

#endif // UTILS_H
