#!/usr/bin/python3
from sys import argv, stdin
from matplotlib import pyplot as plt

def main( argc, argv ):
  exec, coords, x, y, radius = argv
  x, y, radius = float( x ), float( y ), float( radius )
  stdin = open( coords, 'r' )
  X = []
  Y = []
  for line in stdin.readlines():
      x, y = map( lambda v: float( v ), line.split( ', ', 2 ) )
      X.append( x )
      Y.append( y )
  fig, ax = plt.subplots()
  plt.plot( [ x ], [ y ], 'ro' )
  circ = plt.Circle( ( x, y ), radius, color='r', fill=False )
  ax.add_patch( circ )
  plt.plot( X, Y, 'bo' )
  plt.show()

if __name__ == '__main__':
  try:
    main( len( argv ), argv )
  except KeyboardInterrupt:
    print( 'successfully interrupted...' )