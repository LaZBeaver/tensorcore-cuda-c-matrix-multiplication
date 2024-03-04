#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int a_r = 3, a_c = 4;
    float a[a_r][a_c];
    for (int i = 0; i < a_r; i++)
        for (int j = 0; j < a_c; j++)
            a[i][j] = (float)rand() / RAND_MAX;

    int b_r = 4, b_c = 3;
    float b[b_r][b_c];
    for (int i = 0; i < b_r; i++)
        for (int j = 0; j < b_c; j++)
            b[i][j] = (float)rand() / RAND_MAX;


    float result[a_r][b_c];

    clock_t begin = clock();

    for (int i = 0; i < a_r; i++)
        for (int j = 0; j < b_c; j++)
            result[i][j] = 0;
    
    clock_t end = clock();

    for (int k = 0; k < a_c; k++){
        for (int i = 0; i < a_r; i++){
            for (int j = 0; j < b_c; j++){
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }


    printf("A is:\n");
    for (int i = 0; i < a_r; i++){
        for (int j = 0; j < a_c; j++)
            printf("%f ", a[i][j]);
        printf("\n");
    }

    printf("B is:\n");
    for (int i = 0; i < b_r; i++){
        for (int j = 0; j < b_c; j++)
            printf("%f ", b[i][j]);
        printf("\n");
    }

    printf("Result is:\n");
    for (int i = 0; i < a_r; i++){
        for (int j = 0; j < b_c; j++)
            printf("%f ", result[i][j]);
        printf("\n");
    }

    printf("The calculation was done in: %fs", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}