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
        return -1; // pa apunta al puntero, *pa es el array
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

int arr_realloc_after_pop(int **arr, size_t *n) {
    if (n == 0)
        return -1;
    int *tmp;

    tmp = realloc(*arr, *n * sizeof(int));
    *arr = tmp;
    return 0;
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

    free(a);
    return 0;
}
