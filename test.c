#include <stdio.h>
#include <stdlib.h>

void init(float *a, int r, int c){
    for (int i = 0; i < r * c; i++)
        a[i] = i;
}

void print(float *a, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++)
            printf("%f ", a[i * c + j]);
        printf("\n");
    }
}

int main(){
    int r = 3;
    int c = 2;

    size_t bytes = r * c * sizeof(float);

    float *a;

    a = (float*)malloc(bytes);

    init(a, r, c);

    for (int t1 = 0; t1 < r; t1++)
        for (int t2 = 0; t2 < c; t2++)
            printf("%f ", a[t1 * c + t2]);

    printf("\n");

    print(a, r, c);

    for (int k = 0; k < r * c; k++)
        printf ("%f ", a[k]);

    return 0;
}