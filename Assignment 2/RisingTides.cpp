#include "RisingTides.h"
#include "GUI/SimpleTest.h"
#include "queue.h"
#include "set.h"

using namespace std;


Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height) {

    int numRows = terrain.numRows();
    int numCols = terrain.numCols();
    Grid<bool> res(numRows, numCols, false);
    if (sources.isEmpty()) {
        return res;
    }

    Queue<GridLocation> queue;
    Set<GridLocation> visited;

    for (GridLocation location: sources) {
        if (terrain[location.row][location.col] <= height) {
            res[location.row][location.col] = true;
            visited.add(location);
            queue.enqueue(location);
        }
    }

    while (!queue.isEmpty()) {
        GridLocation curLocation = queue.dequeue();
        Vector<GridLocation> adjs;

        if (terrain.inBounds(curLocation.row+1,curLocation.col) && !visited.contains({curLocation.row+1,curLocation.col})) {
            GridLocation t(curLocation.row+1, curLocation.col);
            adjs.add(t);
            visited.add(t);
        }
        if (terrain.inBounds(curLocation.row-1,curLocation.col) && !visited.contains({curLocation.row-1,curLocation.col})) {
            GridLocation t(curLocation.row-1, curLocation.col);
            adjs.add(t);
            visited.add(t);
        }
        if (terrain.inBounds(curLocation.row,curLocation.col+1) && !visited.contains({curLocation.row,curLocation.col+1})) {
            GridLocation t(curLocation.row, curLocation.col+1);
            adjs.add(t);
            visited.add(t);
        }
        if (terrain.inBounds(curLocation.row,curLocation.col-1) && !visited.contains({curLocation.row,curLocation.col-1})) {
            GridLocation t(curLocation.row, curLocation.col-1);
            adjs.add(t);
            visited.add(t);
        }
        for (GridLocation l: adjs) {
            if (terrain[l.row][l.col]<=height) {
                res[l.row][l.col] = true;
                queue.enqueue(l);
            }
        }

    }

    return res;
}

//Vector<GridLocation> getAdjacents(Grid<bool> grid, Set<GridLocation>& visited, GridLocation location) {
//    Vector<GridLocation> res;
//    if (grid.inBounds(location.row+1,location.col) && !visited.contains(location)) {
//        GridLocation t(location.row+1, location.col);
//        res.add(t);
//        visited.add(t);
//    }
//    if (grid.inBounds(location.row-1,location.col) && !visited.contains(location)) {
//        GridLocation t(location.row-1, location.col);
//        res.add(t);
//        visited.add(t);
//    }
//    if (grid.inBounds(location.row,location.col+1) && !visited.contains(location)) {
//        GridLocation t(location.row, location.col+1);
//        res.add(t);
//        visited.add(t);
//    }
//    if (grid.inBounds(location.row,location.col-1) && !visited.contains(location)) {
//        GridLocation t(location.row, location.col-1);
//        res.add(t);
//        visited.add(t);
//    }

//    return res;
//}


/***** Test Cases Below This Point *****/
PROVIDED_TEST("Nothing gets wet if there are no water sources.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        // empty
    };

    /* There are no water sources, so nothing should be underwater. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Everything gets wet if all locations are below the water level.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Everything should flood; there are no barriers to stop the water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true,  true },
        {  true,  true,  true },
        {  true,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a vertical levee.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 0, 2, 0 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Only locations to the left of the barrier should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true, false, false },
        {  true, false, false },
        {  true, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a diagonal levee.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Water only flows in the four cardinal directions, so it can't
     * pass through the barrier. Only the top should be flooded.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't flow diagonally.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 2, 0, 2 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* Water should be trapped in the center, since it can't move
     * diagonally.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false,  true, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow in all cardinal directions.") {
    Grid<double> world = {
        { 2, 0, 2 },
        { 0, 0, 0 },
        { 2, 0, 2 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* The water in this case should flow up, down, left, and right. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false,  true, false },
        {  true,  true,  true },
        { false,  true, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow from multiple sources.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 },
        { 2, 2 }
    };

    /* Everything except the levee should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false,  true },
        { false,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Handles asymmetric worlds and non-square grids") {
    Grid<double> world = {
        { 3, 1, 4, 1 },
        { 5, 9, 2, 6 },
        { 5, 3, 5, 8 }
    };

    /* Initial test - water shouldn't leak out from the 2 if the height is 3.5. */
    Vector<GridLocation> sources = {
        { 1, 2 }
    };

    Grid<bool> expected = {
        { false, false, false, false },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 3.5), expected);

    /* Now, increase the water height to 4.5. */
    expected = {
        {  true,  true,  true,  true },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 4.5), expected);

    /* Now, increase the water height to 5.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true, false },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 5.5), expected);

    /* Now, increase the water height to 6.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true,  true },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 6.5), expected);

    /* Now, increase the water height to 9.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 9.5), expected);
}

PROVIDED_TEST("Stress test: Handles a large, empty world quickly.") {
    Grid<double> world(100, 100); // Large world, everything defaults to 0 height.
    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* This may take a long time to complete if the solution is inefficient. Look
     * for things like
     *
     * 1. passing around large objects by *value* rather than by *reference*,
     * 2. revisiting the same squares multiple times (e.g. flooding the same
     *    cell many times due to not checking if something is flooded),
     *
     * etc.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    EXPECT_EQUAL(water.numRows(), world.numRows());
    EXPECT_EQUAL(water.numCols(), world.numCols());

    /* Everything should be flooded. */
    for (int row = 0; row < world.numRows(); row++) {
        for (int col = 0; col < world.numCols(); col++) {
            EXPECT_EQUAL(water[row][col], true);
        }
    }
}
