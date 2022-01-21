#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "points.h"

uint64_t parse_radius( char const* const );

int point_fscanf( FILE* const, struct point* );

static inline size_t count_solutions( size_t points ) {
  return ( points << 1 ) - 1;
}

#endif /* _UTILS_H_ */