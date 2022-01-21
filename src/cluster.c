#include "cluster.h"


double centroid( struct cluster_header cl1, struct cluster_header cl2, metric* rho ) {
    const double dist = rho( ( struct point ) { .x = cl1.centre_x, .y = cl1.centre_y }, ( struct point ) { .x = cl2.centre_x, .y = cl2.centre_y } );
    return dist * dist;
}


bool** clusters_init( size_t clusters, struct cluster_header** ptr_headers, struct points points ) {
  /* init headers of clusters */
  *ptr_headers = malloc( sizeof( struct cluster_header ) * clusters );

  /* init matrix of clusters' points */
  bool** matrix = ( bool** ) malloc( sizeof( bool* ) * clusters );
  for ( size_t i = 0; i < clusters; ++i ) {
      matrix[ i ] = ( bool* ) malloc( sizeof( bool ) * points.count );
      for ( size_t j = 0; j < points.count; ++j )
          matrix[ i ][ j ] = false;
  }

  /* init with basic values */
  for ( size_t i = 0; i < points.count; ++i ) {
    matrix[ i ][ i ] = true;
    ( *ptr_headers )[ i ] = ( struct cluster_header ) {
        .centre_x = ( double ) points.x.data[ i ],
        .centre_y = ( double ) points.y.data[ i ],
        .points = 1
    };
  }
  return matrix;
}


void clusters_linkage( size_t cl_headers_length, struct cluster_header* cl_headers, size_t cl_length, bool** clusters, method* d, metric* rho ) {
  /* uniting */
  for ( size_t i = 0; i < cl_headers_length - cl_length; ++i ) {
    const size_t idx = cl_length + i;
    double crit = DBL_MAX;
    size_t unite_j = 0;
    size_t unite_k = 1;
    for ( size_t j = 0; j < cl_length - 1 + i; ++j )
      if ( !cl_headers[ j ].is_united )
        for ( size_t k = j + 1; k < cl_length + i; ++k ) {
          double maybe_crit = d( cl_headers[ j ], cl_headers[ k ], rho );
          if ( !cl_headers[ k ].is_united && maybe_crit < crit ) {
            unite_j = j;
            unite_k = k;
            crit = maybe_crit;
          }
        }
    
    cl_headers[ unite_j ].is_united = true;
    cl_headers[ unite_k ].is_united = true;
    const size_t n = cl_headers[ unite_j ].points + cl_headers[ unite_k ].points;
    const double X_j = cl_headers[ unite_j ].centre_x * cl_headers[ unite_j ].points;
    const double X_k = cl_headers[ unite_k ].centre_x * cl_headers[ unite_k ].points;
    const double Y_j = cl_headers[ unite_j ].centre_y * cl_headers[ unite_j ].points;
    const double Y_k = cl_headers[ unite_k ].centre_y * cl_headers[ unite_k ].points;
    cl_headers[ idx ] = ( struct cluster_header ) {
      .centre_x = ( X_j + X_k ) / n,
      .centre_y = ( Y_j + Y_k ) / n,
      .points = n,
      .is_united = false
    };

    for ( size_t j = 0; j < cl_length; ++j )
      clusters[ idx ][ j ] = clusters[ unite_j ][ j ] || clusters[ unite_k ][ j ];
  }
  /* uniting */
}


void clusters_calculate_hits( size_t cl_headers_length, struct cluster_header* cl_headers, size_t cl_length, bool** clusters, struct points points, uint64_t radius, metric* rho ) {
  for ( size_t i = 0; i < cl_headers_length; ++i ) {
    cl_headers[ i ].hits = 0;
    for ( size_t j = 0; j < cl_length; ++j )
      if ( clusters[ i ][ j ] )
        if ( rho( point_from( cl_headers[ i ].centre_x, cl_headers[ i ].centre_y ),
                      point_from( points.x.data[ j ], points.y.data[ j ] ) ) <= radius )
          cl_headers[ i ].hits += 1;
  } 
}


struct cluster_header clusters_find_best_header_by_hits( size_t cl_headers_length, struct cluster_header* cl_headers ) {
  struct cluster_header best = cl_headers[ 0 ];
    for ( size_t i = 1; i < cl_headers_length; ++i )
      if ( best.hits < cl_headers[ i ].hits )
        best = cl_headers[ i ];
  return best;
}

void clusters_destroy( size_t cl_headers_length, struct cluster_header* cl_headers, bool** clusters ) {
  free( cl_headers );
  for ( size_t i = 0; i < cl_headers_length; ++i )
      free( clusters[ i ] );
  free( clusters );
}