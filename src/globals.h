#pragma once
#include <stdint.h>

typedef struct dimensions {
    int width, height;
} dimensions;
extern dimensions windDim;

typedef struct color_t {
    uint8_t r,g,b;
} color;
extern color backgroundColor;
extern color lineColor;
extern color settingEntityColor;
extern color runningEntityColor;

typedef struct point_t {
    int x,y;
} point;

extern const int gridColumns;
extern const int gridRows;

extern point* gridCache;

extern dimensions tile;