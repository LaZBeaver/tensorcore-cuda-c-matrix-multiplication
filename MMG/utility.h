#include <stdio.h>
#include <stdlib.h>


//--------------------------------------------
typedef struct
{
    int row;
    int column;
    int *data;
} imat;

typedef struct
{
    int row;
    int column;
    float *data;
} fmat;

//--------------------------------------------
//Generating random number
int irng(int low, int high)
{
    return (rand() % (high - low)) + low;
}

float frng(float low, float high)
{
    return (((float)rand()) / ((float)RAND_MAX)) * (high - low) + low;
}
//--------------------------------------------
//Allocationg matrix memory
imat* mallocIm(int row, int column)
{
    imat* mat = (imat*) malloc(sizeof(imat));
    if (mat == NULL)
    {   
        perror("Couldn't allocate memory for matrix\n");
        return NULL;
    }
    mat->data = (int*) malloc(row * column * sizeof(int));
    if (mat->data == NULL)
    {
        perror("Couldn't allocate memory for data\n");
        free(mat);
        return NULL;
    }

    mat->row = row;
    mat->column = column;

    return mat;
}

fmat* mallocFm(int row, int column)
{
    fmat* mat = (fmat*) malloc(sizeof(fmat));
    if (mat == NULL)
    {   
        perror("Couldn't allocate memory for matrix\n");
        return 0;
    }
    mat->data = (float*) malloc(row * column * sizeof(float));
    if (mat->data == NULL)
    {
        perror("Couldn't allocate memory for data\n");
        free(mat);
        return 0;
    }

    mat->row = row;
    mat->column = column;

    return mat;
}
//--------------------------------------------
//Generating random or Identity matrix
imat* irmg(int row, int column, int eye)
{
    imat* mat = mallocIm(row, column);
    if (mat == NULL)
    {
        return NULL;
    }
    
    if (eye)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (i == j)
                {
                    *(mat->data + i * column + (j)) = 1;
                }
                else
                {
                    *(mat->data + i * column + (j)) = 0;
                }
            }
        
        }   
    }
    else
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                *(mat->data + i * column + (j)) = irng(1, 10);
            }
        
        }
    }
    
    return mat;
}

fmat* frmg(int row, int column, int eye)
{
    fmat* mat = mallocFm(row, column);
    if (mat == NULL)
    {
        return NULL;
    }

    if (eye)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (i == j)
                {
                    *(mat->data + i * column + (j)) = 1;
                }
                else
                {
                    *(mat->data + i * column + (j)) = 0;
                }
            }
        
        }   
    }
    else
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                *(mat->data + i * column + (j)) = frng(1, 10);
            }
        
        }
    }

    return mat;
}
//--------------------------------------------
//Generating matrix of zeroes
imat* izeros(int row, int column)
{
    imat* mat = mallocIm(row, column);
    if (mat == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            *(mat->data + i * column + (j)) = 0;
        }
        
    }

    return mat;
}

fmat* fzeros(int row, int column)
{
    fmat* mat = mallocFm(row, column);
    if (mat == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            *(mat->data + i * column + (j)) = 0;
        }
        
    }

    return mat;
}
//--------------------------------------------
//Printing matrix onto screen
void printIm(imat* mat)
{
    for (int i = 0; i < mat->row; i++)
    {
        for (int j = 0; j < mat->column; j++)
        {
            if (j == mat->column - 1)
            {
                printf("%d\n", *(mat->data + i * mat->column + (j)));
            }
            else
            {
                printf("%d, ", *(mat->data + i * mat->column + (j)));
            }
        }
    }  
}

void printFm(fmat* mat)
{
    for (int i = 0; i < mat->row; i++)
    {
        for (int j = 0; j < mat->column; j++)
        {
            if (j == mat->column - 1)
            {
                printf("%f\n", *(mat->data + i * mat->column + (j)));
            }
            else
            {
                printf("%f, ", *(mat->data + i * mat->column + (j)));
            }
        }
    }  
}
//--------------------------------------------
//Freeing matrix memory
void freeIm(imat* mat)
{
    free(mat->data);
    free(mat);
}

void freeFm(fmat* mat)
{
    free(mat->data);
    free(mat);
}
//--------------------------------------------































