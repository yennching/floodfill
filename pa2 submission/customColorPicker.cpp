#include "customColorPicker.h"

customColorPicker::customColorPicker(HSLAPixel fillColor, int stripeSpacing){
    color = fillColor;
    spacing = stripeSpacing;
}

HSLAPixel customColorPicker::operator()(int x, int y){

    if ( ((x % spacing) == 0) || ((y % spacing) ==0) ){
        return color;
    }
    else{
        HSLAPixel * white = new HSLAPixel();
        return * white;
    }
}