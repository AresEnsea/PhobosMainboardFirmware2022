#include "strategy.h"

Strategy* strategy_initialize() {
    Strategy* strategy = (Strategy*) malloc(sizeof(Strategy));
    strategy->length = 12;
    strategy->path = (Bezier**) malloc(sizeof(Bezier*) * strategy->length);

    strategy->directions = (Direction*) malloc(sizeof(Direction) * strategy->length);
    strategy->speeds = (float*) calloc(strategy->length+1, sizeof(float));

    strategy->onSiteActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
    strategy->onSiteActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));
    strategy->onMoveActions = (uint8_t**) malloc(sizeof(uint8_t*) * (strategy->length+1));
    strategy->onMoveActionsLengths = (int*) calloc((strategy->length+1), sizeof(int));

    strategy->path[0] = bezier_new(119.969, 879.929, 178.004, 880.012, 440.576, 851.894, 572.422, 1018.733, 30);
    strategy->path[1] = bezier_new(572.422, 1018.733, 704.269, 1185.571, 605.615, 1388.480, 510.343, 1485.028, 30);
    strategy->path[2] = bezier_new(510.343, 1485.028, 415.070, 1581.576, 435.653, 1569.172, 385.564, 1614.828, 30);
    strategy->path[3] = bezier_new(385.564, 1614.828, 185.559, 1420.743, 227.721, 912.121, 226.543, 616.533, 30);
    strategy->path[4] = bezier_new(226.543, 616.533, 225.365, 320.945, 225.207, 311.644, 223.404, 156.592, 30);
    strategy->path[5] = bezier_new(223.404, 156.592, 223.848, 443.925, 223.174, 511.307, 233.619, 846.817, 30);
    strategy->path[6] = bezier_new(233.619, 846.817, 244.065, 1182.327, 308.785, 1439.988, 362.240, 1556.043, 30);
    strategy->path[7] = bezier_new(362.240, 1556.043, 415.695, 1672.097, 550.885, 1798.591, 677.165, 1799.998, 30);
    strategy->path[8] = bezier_new(677.165, 1799.998, 760.999, 1800.447, 809.049, 1800.407, 863.127, 1799.892, 30);
    strategy->path[9] = bezier_new(863.127, 1799.892, 917.119, 1799.719, 989.549, 1799.801, 1044.142, 1799.815, 30);
    strategy->path[10] = bezier_new(1044.142, 1799.815, 1098.736, 1799.662, 1172.146, 1799.798, 1216.696, 1800.056, 30);
    strategy->path[11] = bezier_new(1216.696, 1800.056, 1215.578, 1634.543, 1238.844, 1467.963, 1068.961, 1471.400, 30);

    strategy->directions[0] = FORWARD;
    strategy->directions[1] = FORWARD;
    strategy->directions[2] = FORWARD;
    strategy->directions[3] = FORWARD;
    strategy->directions[4] = FORWARD;
    strategy->directions[5] = FORWARD;
    strategy->directions[6] = FORWARD;
    strategy->directions[7] = FORWARD;
    strategy->directions[8] = FORWARD;
    strategy->directions[9] = FORWARD;
    strategy->directions[10] = FORWARD;
    strategy->directions[11] = FORWARD;

    strategy->speeds[1] = 1000;
    strategy->speeds[2] = 163;
    strategy->speeds[4] = 870;
    strategy->speeds[6] = 866;
    strategy->speeds[7] = 636;

    strategy->onSiteActionsLengths[0] = 1;
    strategy->onSiteActions[0] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onSiteActions[0][0] = 0xA1;
    strategy->onSiteActionsLengths[3] = 1;
    strategy->onSiteActions[3] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onSiteActions[3][0] = 0xB1;
    strategy->onSiteActionsLengths[5] = 1;
    strategy->onSiteActions[5] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onSiteActions[5][0] = 0xB2;
    strategy->onSiteActionsLengths[8] = 1;
    strategy->onSiteActions[8] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onSiteActions[8][0] = 0xC1;
    strategy->onSiteActionsLengths[9] = 1;
    strategy->onSiteActions[9] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onSiteActions[9][0] = 0xC2;
    strategy->onSiteActionsLengths[10] = 1;
    strategy->onSiteActions[10] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onSiteActions[10][0] = 0xC3;
    strategy->onSiteActionsLengths[11] = 1;
    strategy->onSiteActions[11] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onSiteActions[11][0] = 0xC4;

    strategy->onMoveActionsLengths[7] = 1;
    strategy->onMoveActions[7] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onMoveActions[7][0] = 0xCA;
    strategy->onMoveActionsLengths[11] = 1;
    strategy->onMoveActions[11] = (uint8_t*) malloc(sizeof(uint8_t) * 1);
    strategy->onMoveActions[11][0] = 0xA4;

    return strategy;
}
