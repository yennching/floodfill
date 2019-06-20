#include "dotColorPicker.h"

dotColorPicker::dotColorPicker(HSLAPixel fillColor, int dotGrid,int dotSize)
{
    color = fillColor;
    spacing = dotGrid;
    size = dotSize;
}

HSLAPixel dotColorPicker::operator()(int x, int y)
{
    HSLAPixel ret;

    int xmod = x % spacing;
    int ymod = y % spacing;

    if (xmod >= spacing - size){
        xmod = spacing - xmod;
    }

    if (ymod >= spacing - size){
        ymod = spacing - ymod;
    }

    int distanceFromNearest = xmod * xmod + ymod * ymod;
    int maximumDistance = size * size;

    if (distanceFromNearest <= maximumDistance) {
        ret = color;
    } else {
        ret.h = 0.; ret.s = 0.; ret.l = 1.;
    }
    
    return ret;
}
