#include "imagefilter.h"

ImageFilter::ImageFilter()
{

}

QImage ImageFilter::greyScale(QImage image)
{
    QColor pxColor, pxGreyScale;
        for(unsigned long int x = 0; x < image.width(); x++)
        {
            for(unsigned long int y = 0; y < image.height(); y++)
            {
                pxColor = image.pixelColor(x, y);
                int grey = (pxColor.red() + pxColor.green() + pxColor.blue()) / 3;
                pxGreyScale.setRed(grey);
                pxGreyScale.setGreen(grey);
                pxGreyScale.setBlue(grey);
                image.setPixelColor(x, y, pxGreyScale);
            }
        }
        return image;
}

QImage ImageFilter::lighten(QImage image, int value)
{
    QColor pxOrg, pxNew;
    for(unsigned long int x = 0; x < image.width(); x++)
    {
        for(unsigned long int y = 0; y < image.height(); y++)
        {
            pxOrg = image.pixelColor(x, y);

            int red = pxOrg.red() + value;
            int green = pxOrg.green() + value;
            int blue = pxOrg.blue() + value;

            if(red > 255) red = 255;
            else if(red < 0) red = 0;
            if(green > 255) green = 255;
            else if(green < 0) green = 0;
            if(blue > 255) blue = 255;
            else if(blue < 0) blue = 0;

            pxNew.setRed(red);
            pxNew.setGreen(green);
            pxNew.setBlue(blue);
            image.setPixelColor(x, y, pxNew);
        }
    }
    return image;
}

QImage ImageFilter::darken(QImage image, int value)
{
    return ImageFilter::lighten(image, value * (-1));
}
