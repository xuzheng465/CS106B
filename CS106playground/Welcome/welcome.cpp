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
#include "queue.h"
#include "simpio.h"
#include "gwindow.h"
using namespace std;


void welcomeAlert(string name)
{
    GWindow* window = new GWindow(300, 200);
    window->setTitle("Fall Quarter 2021");
    window->setLocation(300, 100);
    window->setExitOnClose(true);
    window->setBackground("White");
    window->clear();
    window->setColor("black");
    window->drawString("Welcome " + name + "!", 75, 175);
    window->drawImage("res/stanford.png", 75, 25);
    window->setColor("#008F00"); // green
    double x = 140, y = 50, w = 15, h = 30;
    for (int i = 0; i < 4; i++) {
        window->fillPolygon({GPoint(x-w, y+h),GPoint(x, y),GPoint(x+w, y+h) } );
        y += h/2;
    }
    window->setVisible(true);
}

void nameDiamond(string name) {
    for (int i = 0; i < name.length(); i++) {
        cout << name.substr(0, i+1) << endl;
    }
    for (int i = 1; i < name.length(); i++) {
        for (int j =0; j<i; j++) {
            cout << " ";
        }
        cout << name.substr(i) << endl;
    }
}

int main2()
{
//    Queue<string> names = {"Leland", "Stanford", "Junior", "University"};
//    cout << "Copyright 2021 " << names << endl;
//    string name = getLine("What is your name?");
//    welcomeAlert(name);
//    return 0;

//    string name = "Oliver";
//    nameDiamond(name);
    ifstream input;
    input.open("afile.txt");
    if (input.fail()) {
        cout << "womp womp" <<endl;
    } else {
        string line;
        int numOfLines = 0;
        while (getline(input, line)) {
            cout << " here is a line: " << line << endl;
            numOfLines++;
        }
        cout << "There were " << numOfLines << " total lines. " << endl;
    }

    return 0;

}
