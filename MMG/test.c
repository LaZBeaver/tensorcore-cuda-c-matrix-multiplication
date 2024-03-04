
//#include "utility.h"
#include "product.h"
#include <time.h>



int main()
{
    srand(7);
    /*
    Inner = 1226 = 20.4 mints
    Outer = 1045 = 17.4 mints
    On 5k,4k * 4k,5k with integer
    */

////////////////////////////////////////////////////////////INNER//////////////////////////////
    // imat* imat1 = irmg(2, 3, 0);
    // imat* imat2 = irmg(3, 4, 0);
    // clock_t begin = clock();
    // imat* imat3 = iinner(imat1, imat2);
    // clock_t end = clock();
    // printIm(imat1);
    // printf("============================\n");
    // printIm(imat2);
    // printf("============================\n");
    // printIm(imat3);
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeIm(imat1);
    // freeIm(imat2);
    // freeIm(imat3);

    // fmat* fmat1 = frmg(2, 3, 0);
    // fmat* fmat2 = frmg(3, 4, 0);
    // clock_t begin = clock();
    // fmat* fmat3 = finner(fmat1, fmat2);
    // clock_t end = clock();
    // printFm(fmat1);
    // printf("============================\n");
    // printFm(fmat2);
    // printf("============================\n");
    // printFm(fmat3);
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeFm(fmat1);
    // freeFm(fmat2);
    // freeFm(fmat3);

    // imat* imat1 = irmg(1024, 1024, 0);
    // imat* imat2 = irmg(1024, 1024, 0);
    // clock_t begin = clock();
    // imat* imat3 = iinner(imat1, imat2);
    // clock_t end = clock();
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeIm(imat1);
    // freeIm(imat2);
    // freeIm(imat3);


    // fmat* fmat1 = frmg(1024, 1024, 0);
    // fmat* fmat2 = frmg(1024, 1024, 0);
    // clock_t begin = clock();
    // fmat* fmat3 = finner(fmat1, fmat2);
    // clock_t end = clock();
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeFm(fmat1);
    // freeFm(fmat2);
    // freeFm(fmat3);


//////////////////////////////////////////////////////////////////OUTER////////////////////////

    // imat* imat1 = irmg(2, 3, 0);
    // imat* imat2 = irmg(3, 4, 0);
    // clock_t begin = clock();
    // imat* imat3 = iouter(imat1, imat2);
    // clock_t end = clock();
    // printIm(imat1);
    // printf("============================\n");
    // printIm(imat2);
    // printf("============================\n");
    // printIm(imat3);
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeIm(imat1);
    // freeIm(imat2);
    // freeIm(imat3);


    // fmat* fmat1 = frmg(2, 3, 0);
    // fmat* fmat2 = frmg(3, 4, 0);
    // clock_t begin = clock();
    // fmat* fmat3 = fouter(fmat1, fmat2);
    // clock_t end = clock();
    // printFm(fmat1);
    // printf("============================\n");
    // printFm(fmat2);
    // printf("============================\n");
    // printFm(fmat3);
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeFm(fmat1);
    // freeFm(fmat2);
    // freeFm(fmat3);


    // imat* imat1 = irmg(1024, 1024, 0);
    // imat* imat2 = irmg(1024, 1024, 0);
    // clock_t begin = clock();
    // imat* imat3 = iouter(imat1, imat2);
    // clock_t end = clock();
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeIm(imat1);
    // freeIm(imat2);
    // freeIm(imat3);


    // fmat* fmat1 = frmg(1024, 1024, 0);
    // fmat* fmat2 = frmg(1024, 1024, 0);
    // clock_t begin = clock();
    // fmat* fmat3 = fouter(fmat1, fmat2);
    // clock_t end = clock();
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeFm(fmat1);
    // freeFm(fmat2);
    // freeFm(fmat3);

////////////////////////////////////////////////////////////////////WINOGRAD///////////////////

    // imat* imat1 = irmg(3, 5, 0);
    // imat* imat2 = irmg(5, 7, 0);
    // clock_t begin = clock();
    // imat* imat3 = iWino(imat1, imat2);
    // clock_t end = clock();
    // printIm(imat1);
    // printf("============================\n");
    // printIm(imat2);
    // printf("============================\n");
    // printIm(imat3);
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeIm(imat1);
    // freeIm(imat2);
    // freeIm(imat3);

    // imat* imat1 = irmg(1024, 1024, 0);
    // imat* imat2 = irmg(1024, 1024, 0);
    // clock_t begin = clock();
    // imat* imat3 = iWino(imat1, imat2);
    // clock_t end = clock();
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeIm(imat1);
    // freeIm(imat2);
    // freeIm(imat3);


    // fmat* fmat1 = frmg(3, 5, 0);
    // fmat* fmat2 = frmg(5, 7, 0);
    // clock_t begin = clock();
    // fmat* fmat3 = fWino(fmat1, fmat2);
    // clock_t end = clock();
    // printFm(fmat1);
    // printf("============================\n");
    // printFm(fmat2);
    // printf("============================\n");
    // printFm(fmat3);
    // printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    // freeFm(fmat1);
    // freeFm(fmat2);
    // freeFm(fmat3);

    fmat* fmat1 = frmg(1024, 1024, 0);
    fmat* fmat2 = frmg(1024, 1024, 0);
    clock_t begin = clock();
    fmat* fmat3 = fWino(fmat1, fmat2);
    clock_t end = clock();
    printf("The calculation was done in: %fs\n", (float)(end - begin) / CLOCKS_PER_SEC);
    freeFm(fmat1);
    freeFm(fmat2);
    freeFm(fmat3);

    return 0;
}









































