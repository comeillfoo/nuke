#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "points.h"
#include "cluster.h"
#include "utils.h"

#define RQ_PARAMS_COUNT 2
#define PARAMS_COUNT ( 1 + RQ_PARAMS_COUNT )

int main( int argc, char** argv ) {

    /* check if enough parameters passed */ 
    if ( argc < PARAMS_COUNT ) {
        fprintf( stderr, "not enough parameters\n" );
        return 1;
    }

    /* process parameters */
    const uint64_t radius = parse_radius( argv[ 2 ] );
    // fprintf( stderr, "[ path=\'%s\', radius=%" PRIu64 " ]\n", argv[ 1 ], radius );
    
    FILE* const coords_f = fopen( argv[ 1 ], "r" );
    /* check if we can work with the parameters */
    if ( coords_f == NULL ) {
        fprintf( stderr, "cannot open file [ %s ]\n", argv[ 1 ] );
        return 1;
    }

    struct points coords = points_init();
    // fprintf( stderr, "vectors successfully created\n" );

    /* read the points */ 
    while ( !feof( coords_f ) ) {
        struct point p = {0};
        if ( point_fscanf( coords_f, &p ) != 2 ) { /* check if file has invalid data format */
            fprintf( stderr, "invalid file format\n" );
            points_free( &coords );
            fclose( coords_f );
            fprintf( stderr, "invalid but successfully freed\n" );
            return 1;
        }
        points_push_back( &coords, p );
    }

    /* free the fd */
    fclose( coords_f );
    // fprintf( stderr, "successfully released file\n" );

    const size_t solutions_count = count_solutions( coords.count );
    // fprintf( stderr, "solutions: %zu\n", solutions_count );

    struct cluster_header* headers = NULL;
    bool** clusters = clusters_init( solutions_count, &headers, coords );

    clusters_linkage( solutions_count, headers, coords.count, clusters, centroid, euclid );

    clusters_calculate_hits( solutions_count, headers, coords.count, clusters, coords, radius, euclid );  

    /* free the coords */
    points_free( &coords );
    // fprintf( stderr, "points successfully freed\n" );

    struct cluster_header best = clusters_find_best_header_by_hits( solutions_count, headers );

    fprintf( stdout, "%lf\t%lf\t%zu\n", best.centre_x, best.centre_y, best.hits );

    clusters_destroy( solutions_count, headers, clusters );
    return 0;
}