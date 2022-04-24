#include "imagefilter.h"

#include <algorithm>

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

// median filter works for width = 3, but not for width >= 5
/** ToDo */
QImage ImageFilter::median(QImage image, int filterWidth)
{
    QColor pxOrg, pxNew;
    int red, green, blue;
    int filterSize, filterHalfSize, filterHalfWidth;
    int padding;
    QImage filteredImage;

    QColor *filterPxArray;
    int *filterRedValues;
    int *filterGreenValues;
    int *filterBlueValues;

    if(filterWidth % 2 != 1) return image;
    filterSize = filterWidth * filterWidth;
    filterHalfSize = filterSize / 2;
    filterHalfWidth = filterWidth / 2;
    padding = filterHalfWidth;

    filterRedValues = new int[filterSize];
    filterGreenValues = new int[filterSize];
    filterBlueValues = new int[filterSize];

    // Arbeitskopie des zu filternden Bildes anfertigen
    filteredImage = image.copy();

    // Bild Zeilenweise durchgehen
    for(unsigned long int y = padding; y < image.height() - padding; y++)
    {
        for(unsigned long int x = padding; x < image.width() - padding; x++)
        {
            for(int j = 0; j < filterWidth; j++)
            {
                for(int i = 0; i < filterWidth; i++)
                {
                    int posX = x - filterHalfWidth + i;
                    int posY = y - filterHalfWidth + j;
                    pxOrg = image.pixelColor(posX, posY);
                    filterRedValues[i + j] = pxOrg.red();
                    filterGreenValues[i + j] = pxOrg.green();
                    filterBlueValues[i + j] = pxOrg.blue();
                }
            }
            std::sort(filterRedValues, filterRedValues + filterSize - 1);
            std::sort(filterGreenValues, filterGreenValues + filterSize - 1);
            std::sort(filterBlueValues, filterBlueValues + filterSize - 1);
            pxNew.setRgb(filterRedValues[filterHalfSize], filterGreenValues[filterHalfSize], filterBlueValues[filterHalfSize]);
            filteredImage.setPixelColor(x, y, pxNew);
        }
    }

    delete[] filterRedValues;
    delete[] filterGreenValues;
    delete[] filterBlueValues;
    return filteredImage.copy(padding, padding, filteredImage.width() - padding * 2, filteredImage.height() - padding * 2);
}
