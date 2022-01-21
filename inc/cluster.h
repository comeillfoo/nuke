#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include <stdio.h>
#include <stdbool.h>
#include <float.h>

#include "points.h"


struct cluster_header {
    double centre_x;
    double centre_y;
    size_t points;
    bool is_united;
    int64_t hits;
};


typedef double method( struct cluster_header, struct cluster_header, metric* );


double centroid( struct cluster_header cl1, struct cluster_header cl2, metric* rho );


bool** clusters_init( size_t, struct cluster_header**, struct points );


void clusters_linkage( size_t, struct cluster_header*, size_t, bool**, method*, metric* );


void clusters_calculate_hits( size_t, struct cluster_header*, size_t, bool**, struct points, uint64_t, metric* );

struct cluster_header clusters_find_best_header_by_hits( size_t, struct cluster_header* );

void clusters_destroy( size_t, struct cluster_header*, bool** );

#endif /* _CLUSTER_H_ */