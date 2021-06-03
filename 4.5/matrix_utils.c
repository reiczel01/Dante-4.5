#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "matrix_utils.h"

void matrix_destroy(struct matrix_t* m) {
    if (m != NULL && m->height > 0) {
        if (m->ptr != NULL) {
            for (int i = 0; m->height > i; i++) {
                if (*(m->ptr + i) != NULL) {
                    free(*(m->ptr + i));
                }
            }
            free(m->ptr);

        }
    }
}
void matrix_destroy_struct(struct matrix_t** m) {
    if (m != NULL) {
        matrix_destroy(*m);
        free(*m);
        *m = NULL;
    }
}
int matrix_create(struct matrix_t* m, int width, int height) { //https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    if (m == NULL || width <= 0 || height <= 0) {
        return 1;
    }
    m->height = height;
    m->width = width;
    m->ptr = NULL;
    m->ptr = (int**)calloc(height, sizeof(int*)); //rzutownaie na wsak¿nik na wskaŸnik plus alokacaj pamiêi dla kolejnych wierszy * iloœæ pamiêci o wielkoœci wska¿nika int
    if (m->ptr == NULL) {
        return 2;
    }
    for (int i = 0; height > i; i++) {
        *(m->ptr + i) = NULL;
        *(m->ptr + i) = calloc(width, sizeof(int));
        if (*(m->ptr + i) == NULL) {
            matrix_destroy(m);
            return 2;
        }
    }
    return 0;
}
struct matrix_t* matrix_create_struct(int width, int height) {
    struct matrix_t* m = calloc(1, sizeof(struct matrix_t));
    if (m == NULL) {
        return NULL;
    }
    int retVal = matrix_create(m, width, height);
    if (retVal != 0) {
        free(m);
        return NULL;
    }
    else {
        return m;
    }
}
int matrix_read(struct matrix_t* m) {
    if (m == NULL || m->height <= 0 || m->width <= 0 || m->ptr == NULL) {
        return 1;
    }
    printf("Podaj wartoœci: ");
    for (int i = 0; m->height > i; i++) {
        for (int j = 0; m->width > j; j++) {
            int temp;
            int check = scanf("%d", &temp);
            if (check != 1) {
                return 2;
            }
            *(*(m->ptr + i) + j) = temp;
        }
    }
    return 0;
}

struct matrix_t* matrix_transpose(const struct matrix_t* m) {
    if (m == NULL || m->ptr == NULL) {
        return NULL;
    }
    struct matrix_t* transpose;
    transpose = matrix_create_struct(m->height, m->width);
    if (transpose == NULL) {
        matrix_destroy_struct(&transpose);
        return NULL;
    }
    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
          
                *(*(transpose->ptr + j) + i) = *(*(m->ptr + i) + j);
                
           
        }
    }
    return transpose;
}

void matrix_display(const struct matrix_t* m) {
    if (m == NULL || m->height <= 0 || m->width <= 0 || m->ptr == NULL) {
        return;
    }
    for (int i = 0; m->height > i; i++) {
        if (*(m->ptr + i) != NULL) {
            for (int j = 0; m->width > j; j++) {
                int temp = *(*(m->ptr + i) + j);
                printf("%d ", temp);
            }
            printf("\n");
        }
    }
}

int matrix_save_b(const struct matrix_t* m, const char* filename) {
    if (filename == NULL || m == NULL || m->ptr == NULL || m->height <= 0 || m->width <= 0) {
        return 1;
    }
    /*int totChar = 0;
    for (int i = 0; *(filename+i) != '\0'; i++) {
        if (*(filename+i) != ' '){
            totChar++;
        }
    }*/
    /*if (m->height == 1 && m->width == 1) {
        return 1;
    }*/
    /*if (totChar > 30) {
        return 1;
    }*/
    FILE* f = fopen(filename, "wb");

    if (f == NULL) {
        return 2;
    }

    fwrite(&m->width, sizeof(unsigned int), 1, f);
    fwrite(&m->height, sizeof(unsigned int), 1, f);

    //printf("Saving rectangles to file = %s\n", filename);
    //for (i = 0; i < m->height; i++) {
        //const struct rectangle_t* rectangle_ptr = *(rectangles + i);
        //printf("%d %d %d %d\n", rectangle_ptr->x, rectangle_ptr->y, rectangle_ptr->width, rectangle_ptr->height);
    fwrite(m->ptr, sizeof(int), m->height * m->width, f);//pokoleji wype³nia czêœci struktury
//}

    fclose(f);
    return 0;
}

int matrix_save_t(const struct matrix_t* m, const char* filename) {
    if (filename == NULL || m == NULL || m->ptr == NULL || m->height <= 0 || m->width <= 0) {
        return 1;
    }
    FILE* f = fopen(filename, "w");

    if (f == NULL) {
        return 2;
    }

    fwrite(&m->width, sizeof(unsigned int), 1, f);
    fwrite(&m->height, sizeof(unsigned int), 1, f);

    //printf("Saving rectangles to file = %s\n", filename);
    //for (i = 0; i < m->height; i++) {
        //const struct rectangle_t* rectangle_ptr = *(rectangles + i);
        //printf("%d %d %d %d\n", rectangle_ptr->x, rectangle_ptr->y, rectangle_ptr->width, rectangle_ptr->height);
    fwrite(m->ptr, sizeof(int), m->height * m->width, f);//pokoleji wype³nia czêœci struktury
//}

    fclose(f);
    return 0;
}
