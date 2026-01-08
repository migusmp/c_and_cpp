#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint8_t *items;
    size_t count;
    size_t capacity;
} Numbers;

#define da_append(xs, x)                                                       \
    do {                                                                       \
        if ((xs).count >= (xs).capacity) {                                     \
            size_t new_cap = (xs).capacity ? (xs).capacity * 2 : 256;          \
                                                                               \
            void *new_items =                                                  \
                realloc((xs).items, new_cap * sizeof(*(xs).items));            \
                                                                               \
            if (!new_items) {                                                  \
                fprintf(stderr, "Out of memory\n");                            \
                exit(1);                                                       \
            }                                                                  \
                                                                               \
            (xs).items = new_items;                                            \
            (xs).capacity = new_cap;                                           \
        }                                                                      \
        (xs).items[(xs).count++] = (x);                                        \
    } while (0)

#define da_remove_at(xs, idx)                                                  \
    do {                                                                       \
        size_t _i = (idx);                                                     \
        if (_i < (xs).count) {                                                 \
            for (size_t _j = _i + 1; _j < (xs).count; _j++) {                  \
                (xs).items[_j - 1] = (xs).items[_j];                           \
            }                                                                  \
            (xs).count--;                                                      \
        }                                                                      \
    } while (0)

#define da_swap_remove(xs, idx)                                                \
    do {                                                                       \
        size_t _i = (idx);                                                     \
        if (_i < (xs).count) {                                                 \
            (xs).items[_i] = (xs).items[(xs).count - 1];                       \
            (xs).count--;                                                      \
        }                                                                      \
    } while (0)

#define da_shrink_to_fit(xs)                                                   \
    do {                                                                       \
        if ((xs).count < (xs).capacity) {                                      \
            void *p = realloc((xs).items, (xs).count * sizeof(*(xs).items));   \
            if (p || (xs).count == 0) {                                        \
                (xs).items = p;                                                \
                (xs).capacity = (xs).count;                                    \
            }                                                                  \
        }                                                                      \
    } while (0)

int main(void) {
    Numbers xs = {0};

    for (uint8_t x = 0; x < 10; x++)
        da_append(xs, x);

    da_remove_at(xs, 3);

    for (size_t i = 0; i < xs.count; i++)
        printf("%u\n", xs.items[i]);

    free(xs.items);
    return 0;
}
