#include "bezier.h"
#include "propulsion.h"

typedef struct {
	int length;
	Bezier** path;
	Direction* directions;
	float* speeds;

} Strategy;

Strategy* strategy_initialize();
