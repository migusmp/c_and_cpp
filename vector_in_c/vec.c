#include "vec.h"
#include "string.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Vec {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
};

void vec_sort(Vec *vec) {
    if (!vec)
        return;
}

void vec_reverse(Vec *vec) {
    if (!vec || vec->size < 2) {
        return;
    }

    size_t i = 0;
    size_t j = vec->size - 1;

    void *tmp = malloc(vec->element_size);
    if (!tmp) {
        return;
    }

    while (i < j) {
        void *a = (char *)vec->data + i * vec->element_size;
        void *b = (char *)vec->data + j * vec->element_size;

        memcpy(tmp, a, vec->element_size);
        memcpy(a, b, vec->element_size);
        memcpy(b, tmp, vec->element_size);

        i++;
        j--;
    }

    free(tmp);
}

void *vec_at(Vec *vec, size_t index) {
    if (!vec) {
        fprintf(stderr, "vec_at: null vector\n");
        return NULL;
    }
    if (index >= vec->size) {
        fprintf(stderr, "vec_at: index out of range\n");
        return NULL;
    }
    return (char *)vec->data + index * vec->element_size;
}

const void *vec_at_const(const Vec *vec, size_t index) {
    if (!vec) {
        fprintf(stderr, "vec_at: null vector\n");
        return NULL;
    }
    if (index >= vec->size) {
        fprintf(stderr, "vec_at: index out of range\n");
        return NULL;
    }
    return (const char *)vec->data + index * vec->element_size;
}
void *vec_get(Vec *vec, size_t index) {
    if (!vec)
        return NULL;
    if (index >= vec->size)
        return NULL;
    return (char *)vec->data + index * vec->element_size;
}

const void *vec_get_const(const Vec *vec, size_t index) {
    if (!vec)
        return NULL;
    if (index >= vec->size)
        return NULL;
    return (const char *)vec->data + index * vec->element_size;
}

void vec_push(Vec *vec, const void *elem) {
    if (!vec || !elem) {
        return;
    }

    /* 1️⃣ Si está lleno, hay que crecer */
    if (vec->size == vec->capacity) {
        size_t new_capacity;

        if (vec->capacity == 0) {
            new_capacity = 1;
        } else {
            new_capacity = vec->capacity * 2;
        }

        /* overflow check */
        if (new_capacity > SIZE_MAX / vec->element_size) {
            fprintf(stderr, "vec_push: size overflow\n");
            return;
        }

        /* realloc para conservar datos */
        void *new_data = realloc(vec->data, new_capacity * vec->element_size);
        if (!new_data) {
            fprintf(stderr, "vec_push: allocation failed\n");
            return;
        }

        vec->data = new_data;
        vec->capacity = new_capacity;
    }

    /* 3️⃣ Copiar el elemento */
    void *dest = (char *)vec->data + vec->size * vec->element_size;
    memcpy(dest, elem, vec->element_size);

    vec->size++;
}

void vec_free(Vec *vec) {
    if (!vec)
        return;

    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    vec->element_size = 0;
}

Vec *vec_new(size_t capacity, size_t element_size) {
    if (element_size == 0) {
        fprintf(stderr, "vec_new: element_size is zero\n");
        return NULL;
    }

    Vec *vec = malloc(sizeof *vec);
    if (!vec) {
        fprintf(stderr, "vec_new: allocation failed\n");
        return NULL;
    }

    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    vec->element_size = element_size;

    if (capacity == 0) {
        return vec;
    }

    if (capacity > SIZE_MAX / element_size) {
        fprintf(stderr, "vec_new: size overflow\n");
        free(vec);
        return NULL;
    }

    vec->data = malloc(capacity * element_size);
    if (!vec->data) {
        fprintf(stderr, "vec_new: allocation failed\n");
        free(vec);
        return NULL;
    }

    vec->capacity = capacity;
    return vec;
}
