#include "Plotter.h"
using namespace std;
#include "strlib.h"

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    double curX = 0;
    double curY = 0;
    bool up = true;
    PenStyle style = {1, "black"};

    for (string line; getline(input, line);) {
        line = toLowerCase(line);
        if (startsWith(line, "pendown")) {
            up = false;
        } else if (startsWith(line, "penup")) {
            up = true;
        } else if (startsWith(line, "pencolor")) {
            Vector<string> res = stringSplit(line, " ");
            string color = res[1];
            style.color = color;
        } else if (startsWith(line, "penwidth")) {
            Vector<string> res = stringSplit(line, " ");
            string width = res[1];
            style.width = stringToReal(width);
        } else if (startsWith(line, "moveabs")) {
            Vector<string> res = stringSplit(line, " ");
            double dstX = stringToReal(res[1]);
            double dstY = stringToReal(res[2]);

            if (!up) { // draw line
                drawLine(curX, curY, dstX, dstY, style);
            }
            // no matter if drawing, update location
            curX = dstX;
            curY = dstY;
        } else if (startsWith(line, "moverel")) {
            Vector<string> res = stringSplit(line, " ");
            double dX = stringToReal(res[1]);
            double dY = stringToReal(res[2]);
            double dstX = curX + dX;
            double dstY = curY + dY;
            if (!up) {
                drawLine(curX, curY, dstX, dstY, style);
            }
            curX = dstX;
            curY = dstY;
        }
    }
}
