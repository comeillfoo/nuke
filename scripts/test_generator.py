#!/usr/bin/python3
from sys import argv, stdout
import random as rand

min_coords, max_coords = ( 1, 20 )

min_coord, max_coord = ( 0, 99 )

def main( argc, argv ):
    if ( argc < 2 ):
        print( 'not enough parameters passed' )
        return
    
    out = argv[ 1 ]
    tests_count = rand.randint( min_coords, max_coords )
    stdout = open( out, 'w+' )
    for i in range( tests_count ):
        stdout.write( f'{rand.randint( min_coord, max_coord )}, {rand.randint( min_coord, max_coord )}\n' )
    stdout.close()


if __name__ == '__main__':
    try:
        main( len( argv ), argv )
    except KeyboardInterrupt:
        print( '\nsuccessfully halted' )