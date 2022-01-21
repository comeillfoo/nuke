#ifndef _POINT_H_
#define _POINT_H_

#include <stdint.h>
#include <math.h>

#include "vector.h"

struct points {
    struct vector_uint8_t x;
    struct vector_uint8_t y;
    size_t count;
};

struct point {
    double x;
    double y;
};

typedef double metric( struct point, struct point );

double euclid( struct point, struct point );

struct point point_from( uint8_t x, uint8_t y );

struct points points_init();

void points_push_back( struct points*, struct point );

void points_free( struct points* );

#endif /* _POINTS_H_ */