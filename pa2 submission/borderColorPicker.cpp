#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance, HSLAPixel center){
    color = fillColor;
    im = img;
    tol = tolerance;
    ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y){
    for (int i = -3; i <= 3; i++){
        for (int j = -3; j <= 3; j++){
            if (i*i + j*j <= 9){
                if (x+i >= im.width() || y+j >= im.height() || x+i < 0 || y+j < 0){
                    return color;
                }
                if (ctr.dist(*im.getPixel(x+i, y+j)) > tol){
                    return color;
                }
            }
        }
    }
    return *im.getPixel(x,y);
}

