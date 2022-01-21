#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>

#define MIN_VECTOR_CAPACITY 16

typedef struct { size_t count; } vector_capacity;

typedef struct { size_t count; } vector_size;

#define DEFINE_PRIMITIVE_VECTOR( type )                                                  \
                                                                                         \
struct vector_##type {                                                                   \
    vector_capacity capacity;                                                            \
    vector_size size;                                                                    \
    type* data;                                                                          \
};                                                                                       \
                                                                                         \
struct vector_##type vector_##type##_init();                                             \
                                                                                         \
void vector_##type##_free( struct vector_##type* ptr_vector );                           \
                                                                                         \
bool is_vector_##type##_full( struct vector_##type const * const ptr_vector );           \
                                                                                         \
void vector_##type##_push_back( struct vector_##type* ptr_vector, type value );          \
                                                                                         \
void vector_##type##_foreach( struct vector_##type* ptr_vector, void (proc)( type ) );   \
                                                                                         \
size_t vector_##type##_get_size( struct vector_##type* ptr_vector );                     \
                                                                                         \
size_t vector_##type##_get_capacity( struct vector_##type* ptr_vector );

DEFINE_PRIMITIVE_VECTOR( uint8_t )

// DEFINE_PRIMITIVE_VECTOR( size_t )

static inline vector_capacity vector_resize( vector_capacity old_capacity ) {
    return ( vector_capacity ) { old_capacity.count + old_capacity.count / 2 };
}

#define DECLARE_PRIMITIVE_VECTOR( type )                                                \
struct vector_##type vector_##type##_init() {                                           \
    struct vector_##type result = {                                                     \
        .capacity = { MIN_VECTOR_CAPACITY },                                            \
        .size = { 0 },                                                                  \
        .data = malloc( sizeof( type ) * MIN_VECTOR_CAPACITY )                          \
    };                                                                                  \
    return result;                                                                      \
}                                                                                       \
                                                                                        \
void vector_##type##_free( struct vector_##type* ptr_vector ) {                         \
    free( ptr_vector->data );                                                           \
}                                                                                       \
                                                                                        \
bool is_vector_##type##_full( struct vector_##type const * const ptr_vector ) {         \
    return ptr_vector->capacity.count == ptr_vector->size.count;                        \
}                                                                                       \
                                                                                        \
void vector_##type##_push_back( struct vector_##type* ptr_vector, type value ) {        \
    if ( is_vector_##type##_full( ptr_vector ) ) {                                      \
        ptr_vector->capacity = vector_resize( ptr_vector->capacity );                   \
        ptr_vector->data = realloc( ptr_vector->data, ptr_vector->capacity.count );     \
    }                                                                                   \
    ptr_vector->data[ ptr_vector->size.count++ ] = value;                               \
}                                                                                       \
                                                                                        \
void vector_##type##_foreach( struct vector_##type* ptr_vector, void (proc)( type ) ) { \
    for ( size_t i = 0; i < ptr_vector->size.count; ++i )                               \
        proc( ptr_vector->data[ i ] );                                                  \
}                                                                                       \
                                                                                        \
size_t vector_##type##_get_size( struct vector_##type* ptr_vector ) {                   \
    return ptr_vector->size.count;                                                      \
}                                                                                       \
                                                                                        \
size_t vector_##type##_get_capacity( struct vector_##type* ptr_vector ) {               \
    return ptr_vector->capacity.count;                                                  \
}

#endif /* _VECTOR_H_ */