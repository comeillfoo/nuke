#!/usr/bin/python3
from sys import argv, stdin, float_info
from math import sqrt

def euclid( vec1, vec2 ):
    sum = 0
    for i in range( len( vec1 ) ):
        dv = vec1[ i ] - vec2[ i ]
        sum += dv * dv
    return sqrt( sum )   

centre = lambda vec: sum( vec ) / len( vec )

def centroid( u, v, rho ):
    ux = [ x[ 0 ] for x in u ]
    uy = [ y[ 1 ] for y in u ]
    vx = [ x[ 0 ] for x in v ]
    vy = [ y[ 1 ] for y in v ]
    dist = rho( ( centre( ux ), centre( uy ) ) , ( centre( vx ), centre( vy ) ) )
    return dist * dist

def init_clusters( points ):
    return [ set( [ point ] ) for point in points ]

def linkage( points, method, metric ):
    clusters = init_clusters( points )
    solutions = []

    while ( len( clusters ) > 1 ):
        solutions.append( clusters.copy() )
        c = float_info.max
        unite_i = None
        unite_j = None

        for i in range( 0, len( clusters ) - 1 ):
            for j in range( i + 1, len( clusters ) ):
                # print( clusters[ i ], clusters[ j ] )
                maybe_c = method( clusters[ i ], clusters[ j ], metric )
                if ( c > maybe_c ):
                    c = maybe_c
                    unite_j = j
                    unite_i = i
        a = clusters.pop( unite_i )
        b = clusters.pop( unite_j - 1 )
        # print( f'united {unite_i} {unite_j} {c}' )
        clusters.append( a | b )


    return solutions

def main( argc, argv ):
    exec, file_path, radius = argv
    radius = int( radius )

    stdin = open( file_path, 'r' )

    points = []
    for line in stdin.readlines():
        x, y = map( lambda v: int( v ), line.split( ', ', 2 ) )
        points.append( ( x, y ) )

    solutions = linkage( points, centroid, euclid )

    coords = []
    for solution in solutions:
        for cluster in solution:
            count = 0
            x = [ point[ 0 ] for point in cluster ]
            y = [ point[ 1 ] for point in cluster ]
            cx = centre( x )
            cy = centre( y )
            for point in cluster:
                if ( euclid( point, ( cx, cy ) ) <= radius ):
                    count += 1
            coords.append( { 'x': cx, 'y': cy, 'count': count, 'points': ( x, y ) } )

    coord = coords[ 0 ]
    for c in coords:
        if ( c[ 'count' ] > coord[ 'count' ] ):
            coord = c
    print( coord[ 'x' ], coord[ 'y' ], coord[ 'count' ], sep='\t' )


    stdin.close()



if __name__ == '__main__':
    try:
        main( len( argv ), argv )
    except KeyboardInterrupt:
        print( '\nsuccessfully halted...' )
        exit( 0 )