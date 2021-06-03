#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "matrix_utils.h"


int main()
{


    //testy:
    struct matrix_t arr = { .width = 0, .height = -5 };

    int array[1][1] = { { 1} };

    int res = matrix_create(&arr, 1, 1);
    for (int i = 0; i < 1; ++i)
        for (int j = 0; j < 1; ++j)
            arr.ptr[i][j] = array[i][j];
    res = matrix_save_b(&arr, "mostwhereneversteambeautypassseetownmultiplystoodif");
    if (res != 0) {
        printf("Funkcja matrix_save_b() powinna zwrócić kod błędu 0, a zwróciła %d", res);
    }

    struct matrix_t matrix;
    int check = 0;
    int height = 0;
    int width = 0;
    printf("Podaj szerokość i wysokość: ");
    check = scanf("%d %d", &width, &height);
    if (check != 2) {
        printf("incorrect input");
        return 1;
    }

    //matrix.width = -3;
    //matrix.height = 7;

    check = matrix_create(&matrix, width, height);
    if (check == 1) {
        printf("incorrect input data");
        return 2;
    }
    else if (check == 2) {
        printf("Failed to allocate memory");
        return 8;
    }


    check = matrix_read(&matrix);
    if (check == 1) {
        printf("incorrect input data");
        matrix_destroy(&matrix);
        return 8;
    }
    else if (check == 2) {
        printf("incorrect input");
        matrix_destroy(&matrix);
        return 1;
    }

    matrix_display(&matrix);
    printf("\n");
    matrix_display(matrix_transpose(&matrix));

    char filename;
    printf("Podaj nazwę pliku");
    int checkChar = scanf("%c", &filename);
    if (checkChar != 1) {
        printf("incorrect input");
        return 1;
    }
    matrix_save_b(&matrix, &filename);
    matrix_save_t(&matrix, &filename);

    matrix_destroy(&matrix);
    return 0;
}
