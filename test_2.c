#include <stdlib.h>
#include <stdio.h>

#define A_B_S 32

int main(){

    int *a;

    for (int i =0; i < A_B_S; i++){
        a = malloc(sizeof(int));
        *a = i;
        printf ("%d ", a[0]);
        free(a);
    }

    return 0;
}