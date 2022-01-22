/*
 * File: welcome.cpp
 * --------------
 * Sample program used to confirm Qt/CS106 install.
 * @author Julie Zelenski
 * @version 2021/09/08
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "random.h"
#include "gobjects.h"
#include "gevent.h"
#include "simpio.h"
#include "gwindow.h"
using namespace std;
void cantorSet(GWindow& window, int x, int y, int length, int levels);
void kochSnowflake(GWindow& window, int x, int y, int size, int levels);
void dropSandOn(Grid<int>& world, int row, int col);

int main()
{
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 3, 3 },
        { 3, 3, 3 }
    };
    dropSandOn(before, 1,1);
    cout << before << endl;

//    GWindow window(800, 600);
//    window.setWindowTitle("CS 106B/X Fractals");
//    window.setColor("Black");
//    cantorSet(window, 100, 100, 500, 8);
    return 0;

}

void cantorSet(GWindow& window, int x, int y, int length, int levels) {
    if (levels >= 1) {
        pause(100);
        cantorSet(window, x, y + 20, length/3, levels - 1);
        cantorSet(window, x+2*length/3, y+20, length/3, levels - 1);
        window.drawLine(x, y, x+length, y);
        window.drawLine(x, y+1, x+length, y+1);



    }
}

void dropSandOn(Grid<int>& world, int row, int col) {
    if (!world.inBounds(row,col)) {
        return;
    }
    if (world[row][col] < 3) {
        world[row][col] += 1;
    } else {
        world[row][col]=0;
        dropSandOn(world, row, col-1);
        dropSandOn(world, row, col+1);
        dropSandOn(world, row+1, col);
        dropSandOn(world, row-1, col);
    }
}
