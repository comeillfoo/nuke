#include "points.h"

double euclid( struct point p1, struct point p2 ) {
    const double dx = p1.x - p2.x;
    const double dy = p1.y - p2.y;
    return sqrt( dx * dx + dy * dy );
}

struct point point_from( uint8_t x, uint8_t y ) {
    return ( struct point ) { .x = ( double ) x, .y = ( double ) y };
}

struct points points_init() {
    return ( struct points ) { .x = vector_uint8_t_init(), .y = vector_uint8_t_init(), .count = 0 };
}

void points_push_back( struct points* points, struct point value ) {
    vector_uint8_t_push_back( &( points->x ), ( uint8_t ) value.x );
    vector_uint8_t_push_back( &( points->y ), ( uint8_t ) value.y );
    points->count++;
}

void points_free( struct points* points ) {
    vector_uint8_t_free( &( points->x ) );
    vector_uint8_t_free( &( points->y ) );
}