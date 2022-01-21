#include "utils.h"

uint64_t parse_radius( char const* const raw_radius ) {
  char* ptr_end = NULL;
  return strtoull( raw_radius, &ptr_end, 10 );
}

int point_fscanf( FILE* const stream, struct point* point ) {
  uint8_t x = 0, y = 0;
  const int result = fscanf( stream, "%" SCNu8 ", %" SCNu8 "\n", &x, &y );
  *point = point_from( x, y );
  return result;
}