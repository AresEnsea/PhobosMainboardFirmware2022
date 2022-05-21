#include "strategy.h"

Strategy* strategy_initialize() {
    Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
    strategy->length = 4;
    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);
    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
    strategy->speeds = (float*) malloc(sizeof(float) * (strategy->length+1));

    strategy->path[0] = bezier_new(1000.090, 699.971, 1100.090, 699.971, 1549.789, 699.873, 1649.789, 699.873, 30);
    strategy->path[1] = bezier_new(1649.789, 699.873, 1650.341, 775.554, 1649.814, 1349.896, 1649.814, 1349.896, 30);
    strategy->path[2] = bezier_new(1649.814, 1349.896, 1649.814, 1349.896, 999.941, 1350.060, 999.941, 1350.060, 30);
    strategy->path[3] = bezier_new(999.941, 1350.060, 999.941, 1350.060, 1000.052, 713.345, 1000.052, 700.011, 30);

    strategy->directions[0] = FORWARD;
    strategy->directions[1] = FORWARD;
    strategy->directions[2] = FORWARD;
    strategy->directions[3] = FORWARD;

    strategy->speeds[0] = 0;
    strategy->speeds[1] = 0;
    strategy->speeds[2] = 0;
    strategy->speeds[3] = 0;
    strategy->speeds[4] = 0;

    return strategy;
}
