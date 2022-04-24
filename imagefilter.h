#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <QImage>
#include <QColor>


class ImageFilter
{
public:
    ImageFilter();

    static QImage greyScale(QImage image);
    static QImage lighten(QImage image, int value);
    static QImage darken(QImage image, int value);
};

#endif // IMAGEFILTER_H
