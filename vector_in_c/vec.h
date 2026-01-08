#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct Vec Vec;

Vec *vec_new(size_t capacity, size_t element_size);
void vec_free(Vec *vec);
void vec_push(Vec *vec, const void *elem);

void *vec_get(Vec *vec, size_t index);
const void *vec_get_const(const Vec *vec, size_t index);

void *vec_at(Vec *vec, size_t index);
const void *vec_at_const(const Vec *vec, size_t index);

void vec_reverse(Vec *vec);

void vec_sort(Vec *vec);

#endif
