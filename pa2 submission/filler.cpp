/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//#include "filler.h"
#include <set>

animation filler::fillDotDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int dotGrid,int dotSize, double tolerance, int frameFreq)
{
    dotColorPicker d(fillColor, dotGrid, dotSize);
    return fill<Stack>(img, x, y, d, tolerance, frameFreq);

}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    borderColorPicker b(borderColor, img, tolerance,*img.getPixel(x,y));
    return fill<Stack>(img, x, y, b, tolerance, frameFreq);

}

animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{

/* example, implemented for you! */
    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillDotBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int dotGrid,int dotSize, double tolerance, int frameFreq)
{
    dotColorPicker d(fillColor, dotGrid, dotSize);
    return fill<Queue>(img, x, y, d, tolerance, frameFreq);

}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    borderColorPicker b(borderColor, img, tolerance,*img.getPixel(x,y));
    return fill<Queue>(img, x, y, b, tolerance, frameFreq);
}

animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
/* example, completed for you! */
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}



template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    
    // animation motion;
    // int counter = 1;


    // OrderingStructure<pair<int,int>> myTracker;
    // set <pair<int,int>> visited;
    // myTracker.add(pair<int,int>(x,y));

    // HSLAPixel centre = *img.getPixel(x,y);
    // *img.getPixel(x,y) = fillColor(x,y);

    // while(!myTracker.isEmpty()) {
    //     pair<int,int> curr = myTracker.remove();
    //    //cout << "SOME LEEWAY" << endl;
    //     // adding children
    
    //     if (x > 0 && y > 0){

            
           
    //         pair<int,int> up = pair<int,int>(x,y-1);
    //         if(visited.find(up) == visited.end() && 
    //             centre.dist(*img.getPixel(up.first,up.second)) <= tolerance){
    //             myTracker.add(up);   // up
    //             cout << "UP" << endl;
    //         }

    //         pair<int,int> left = pair<int,int>(x-1,y);
    //          if(visited.find(left) == visited.end() && 
    //             centre.dist(*img.getPixel(left.first,left.second)) <= tolerance){
    //             myTracker.add(left);
    //             cout << "LEFT" << endl;
    //         }

    //         pair<int,int> down = pair<int,int>(x,y+1);
    //         if(visited.find(down) == visited.end() && 
    //             centre.dist(*img.getPixel(down.first,down.second)) <= tolerance){
    //             myTracker.add(down);
    //             cout << "DOWN" << endl;
    //         }

    //         pair<int,int> right = pair<int,int>(x+1,y);
    //          if(visited.find(right) == visited.end() && 
    //             centre.dist(*img.getPixel(right.first,right.second)) <= tolerance){
    //             myTracker.add(right);
    //             cout << "RIGHT" << endl;
    //         }
           

            
               
    //         if (visited.find(curr) == visited.end()){
    //             *img.getPixel(curr.first,curr.second) = fillColor(curr.first,curr.second);
    //              visited.insert(curr);
    //              cout << "CURRENT" << endl;
    //         }

    //         counter++;
            
    //         if (counter % frameFreq == 0){
    //             cout << "GIMME MOULAH" << endl;
    //             motion.addFrame(img);
    //         }
    //     }
    

    // }

    // motion.addFrame(img);
    // return motion;


    int counter = 0;
    int width = img.width();
    int height = img.height();
    animation motion;
    HSLAPixel centre = *img.getPixel(x, y);
    OrderingStructure<pair<int, int>> myTracker;
    
    vector<vector<bool>> visited(width, vector<bool>(height, false));

    
    myTracker.add(make_pair(x,y));
    *img.getPixel(x, y) = fillColor.operator()(x,y);
    visited[x][y] = true;
    counter++;

    

    auto checkValid = [&] (int a, int b) {
        bool horizontalBorder = a >= 0 && a < width;
        bool verticalBorder   = b >= 0 && b < height;
        bool withinBounds = horizontalBorder && verticalBorder;

        return withinBounds && centre.dist(*img.getPixel(a,b)) <= tolerance;
    };

    auto process = [&] (int a, int b) {
        myTracker.add(make_pair(a,b));
        *img.getPixel(a,b) = fillColor.operator()(a,b);
        visited[a][b] = true;
        counter++;

        if (counter % frameFreq == 0)
            motion.addFrame(img);
    };

    while (!myTracker.isEmpty()){

        pair<int, int> curr = myTracker.remove(); 
        int xpos = 0;
        int ypos = 0;
        // Pixel located above
        xpos = curr.first;
        ypos = curr.second - 1;
        if (checkValid(xpos, ypos) && visited[xpos][ypos] == false){
            process(xpos, ypos); 
        }

        // Pixel located to the left 
        xpos = curr.first - 1;
        ypos = curr.second;

        if (checkValid(xpos, ypos) && visited[xpos][ypos] == false){
            process(xpos, ypos); 
        }

        // Pixel located below 
        xpos = curr.first;
        ypos = curr.second + 1;

        if (checkValid(xpos, ypos) && visited[xpos][ypos] == false){
            process(xpos, ypos); // Steps: 1-1 to 1-4
        }
        
        // Pixel located to the right 
        xpos = curr.first + 1;
        ypos = curr.second;

        if (checkValid(xpos, ypos) && visited[xpos][ypos] == false){
            process(xpos, ypos); // Steps: 1-1 to 1-4
        }
    }

    motion.addFrame(img); // add last frame
    return motion;


    

    // UP(-y), LEFT(-x), DOWN(+y), RIGHT(+x)
    
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure(OS), marking it processed
     * 
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure. 
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed
     *  neighbors whose color values are 
     *              within (or equal to) tolerance distance from the center, 
     *              to the ordering structure.
     *        2.    use the colorPicker to set the new color of the point.
     *        3.    mark the point as processed
     * .
     *        4.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
    *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 4 neighbors, consisting of 
     *        the 4 pixels who share an edge p. (We leave it to
     *        you to describe those 4 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** UP(-y), LEFT(-x), DOWN(+y), RIGHT(+x)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction. 
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */

    /* your code here */

} 
