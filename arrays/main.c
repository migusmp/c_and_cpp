#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int push_x_on_arr(int **arr, size_t *n, int new_value) {
    int *tmp = realloc(*arr, (*n + 1) * sizeof(int));
    if (!tmp)
        return -1;

    tmp[*n] = new_value;
    *arr = tmp;
    (*n)++;
    return 0;
}

int pop_on_arr(int **arr, size_t *n) {
    if (*n == 0) {
        return -1;
    }
    (*n)--;
    return 0;
}

int arr_remove_at(int *a, size_t *n, size_t k) {
    if (!a || !n)
        return -1;
    if (*n == 0)
        return -1;
    if (k >= *n)
        return -1;

    memmove(&a[k], &a[k + 1], (*n - k - 1) * sizeof *a);

    (*n)--;
    return 0;
}

int arr_remove_at_with_reference(int **pa, size_t *n, size_t k) {
    if (!pa || !*pa || !n)
        return -1;
    if (*n == 0)
        return -1;
    if (k >= *n)
        return -1;

    // Mover a la izquierda: [k+1 .. n-1] -> [k .. n-2]
    size_t move_count = *n - k - 1; // nº de elementos a mover
    memmove(&(*pa)[k], &(*pa)[k + 1], move_count * sizeof **pa);

    // Reducir tamaño lógico
    (*n)--;

    return 0;
}

int insert_on_arr(int **pa, size_t *n, size_t i, int newValue) {
    if (i > *n)
        return -1;

    memmove(&(*pa)[i + 1], &(*pa)[i], (*n - i) * sizeof **pa);
    (*pa)[i] = newValue;
    (*n)++;

    return 0;
}

int arr_realloc_after_pop(int **arr, size_t *n) {
    if (n == 0)
        return -1;
    int *tmp;

    tmp = realloc(*arr, *n * sizeof(int));
    *arr = tmp;
    return 0;
}

int *clone_arr(int **src, size_t *n) {
    if (!src || n == 0)
        return NULL;

    int *dst = malloc(*n * sizeof(int));
    if (!dst)
        return NULL;

    memcpy(dst, (*src), *n * sizeof(int));

    return dst;
}

int *concat_int_arrays(const int *a, size_t na, const int *b, size_t nb,
                       size_t *out_n) {
    if (!out_n)
        return NULL;
    *out_n = 0;

    if ((!a && na) || (!b && nb))
        return NULL;

    size_t total = na + nb;
    if (total == 0)
        return NULL;

    int *res = malloc(total * sizeof(int));
    if (!res)
        return NULL;

    if (na)
        memcpy(res, a, na * sizeof(int));
    if (nb)
        memcpy(res + na, b, nb * sizeof(int));

    *out_n = total;
    return res;
}

void print_arr(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void) {
    size_t n = 5;

    int *a = malloc(n * sizeof(int));
    if (!a)
        return 1;

    for (size_t i = 0; i < n; i++)
        a[i] = (int)i;

    print_arr(a, n);
    push_x_on_arr(&a, &n, 40);
    print_arr(a, n);
    pop_on_arr(&a, &n);
    print_arr(a, n);

    arr_realloc_after_pop(&a, &n);
    push_x_on_arr(&a, &n, 50);
    print_arr(a, n);

    arr_remove_at(a, &n, 1);
    arr_realloc_after_pop(&a, &n);
    print_arr(a, n);

    arr_remove_at(a, &n, 1);
    arr_realloc_after_pop(&a, &n);
    print_arr(a, n);

    arr_remove_at_with_reference(&a, &n, 1);
    arr_realloc_after_pop(&a, &n);
    print_arr(a, n);

    printf("INSERTANDO EN EL ARRAY...\n");
    insert_on_arr(&a, &n, 1, 30);
    print_arr(a, n);

    printf("arr cloned..\n");
    int *arr_cloned = clone_arr(&a, &n);
    print_arr(arr_cloned, n);

    printf("arr concat..\n");
    size_t concated_len;
    int *concated_arrs = concat_int_arrays(a, n, arr_cloned, n, &concated_len);
    print_arr(concated_arrs, concated_len);

    free(a);
    free(arr_cloned);
    free(concated_arrs);
    return 0;
}
