#include "globals.h"
#include <stdlib.h>
#define GRID_ROWS 40
#define GRID_COLUNMS 40
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

dimensions windDim = {WINDOW_WIDTH, WINDOW_HEIGHT};

color backgroundColor = {19, 18, 28};
color lineColor = {43, 46, 43};
color settingEntityColor = {214, 24, 36};
color runningEntityColor = {11, 212, 11};

const int gridRows = GRID_ROWS;
const int gridColumns = GRID_COLUNMS;

point* gridCache = NULL;

dimensions tile = {WINDOW_HEIGHT / GRID_COLUNMS, WINDOW_HEIGHT / GRID_ROWS};
