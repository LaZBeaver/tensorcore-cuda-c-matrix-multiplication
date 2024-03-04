#include "utility.h"


imat* iinner(imat* mat1, imat* mat2)
{
    if (mat1->column != mat2->row)
    {
        perror("Dimension mismatch \n");
        return NULL;
    }
    
    imat* mat_result = izeros(mat1->row, mat2->column);
    if (mat_result == NULL)
    {
        return NULL;
    }
    

    for (int i = 0; i < mat1->row; i++)
    {
        for (int j = 0; j < mat2->column; j++)
        {
            for (int k = 0; k < mat2->row; k++)
            {
                *(mat_result->data + i * mat_result->column + j) += *(mat1->data + i * mat1->column + k) * *(mat2->data + k * mat2->column + j);
            }
        }
    }

    return mat_result;
}


fmat* finner(fmat* mat1, fmat* mat2)
{
    if (mat1->column != mat2->row)
    {
        perror("Dimension mismatch \n");
        return NULL;
    }
    
    fmat* mat_result = fzeros(mat1->row, mat2->column);
    if (mat_result == NULL)
    {
        return NULL;
    }
    

    for (int i = 0; i < mat1->row; i++)
    {
        for (int j = 0; j < mat2->column; j++)
        {
            for (int k = 0; k < mat2->row; k++)
            {
                *(mat_result->data + i * mat_result->column + j) += *(mat1->data + i * mat1->column + k) * *(mat2->data + k * mat2->column + j);
            }         
        }
    }

    return mat_result;
}


imat* iouter(imat* mat1, imat* mat2)
{
    if (mat1->column != mat2->row)
    {
        perror("Dimension mismatch \n");
        return NULL;
    }
    
    imat* mat_result = izeros(mat1->row, mat2->column);
    if (mat_result == NULL)
    {
        return NULL;
    }
    
    for (int k = 0; k < mat2->row; k++)
    {
        for (int i = 0; i < mat1->row; i++)
        {
            for (int j = 0; j < mat2->column; j++)
            {                
                *(mat_result->data + i * mat_result->column + j) += *(mat1->data + i * mat1->column + k) * *(mat2->data + k * mat2->column + j);
            }
        }
    }

    return mat_result;
}


fmat* fouter(fmat* mat1, fmat* mat2)
{
    if (mat1->column != mat2->row)
    {
        perror("Dimension mismatch \n");
        return NULL;
    }
    
    fmat* mat_result = fzeros(mat1->row, mat2->column);
    if (mat_result == NULL)
    {
        return NULL;
    }
    
    for (int k = 0; k < mat2->row; k++)
    {
        for (int i = 0; i < mat1->row; i++)
        {
            for (int j = 0; j < mat2->column; j++)
            {                
                *(mat_result->data + i * mat_result->column + j) += *(mat1->data + i * mat1->column + k) * *(mat2->data + k * mat2->column + j);
            }
        }
    }

    return mat_result;
}


//===============================================================
//***************************************************************
imat* iWino(imat* mat1, imat* mat2)
{
    if (mat1->column != mat2->row)
    {
        perror("Dimension mismatch!\n");
        return NULL;
    }
    

    imat* mat_result = izeros(mat1->row, mat2->column);
    if (mat_result == NULL)
    {
        return NULL;
    }

    int a, b, c, d;
    a = b = c = d = 0;
    int A, B, C, D;
    A = B = C = D = 0;
    int u, v, w;
    u = v = w = 0;
    

    for (int i = 0; i < mat1->row; i+=2)
    {
        for (int j = 0; j < mat2->column; j+=2)
        {
            for (int k = 0; k < mat2->row; k+=2)
            {
                a = *(mat1->data + (i * mat1->column) + k);
                b = *(mat1->data + (i * mat1->column) + (k + 1));
                c = *(mat1->data + ((i + 1) * mat1->column) + k);
                d = *(mat1->data + ((i + 1) * mat1->column) + (k + 1));

                A = *(mat2->data + (k * mat2->column) + j);
                C = *(mat2->data + (k * mat2->column) + (j + 1));
                B = *(mat2->data + ((k + 1) * mat2->column) + j);
                D = *(mat2->data + ((k + 1) * mat2->column) + (j + 1));

                if (k + 1 >= mat1->column)
                {
                    b = 0;
                    d = 0;
                }
                if (i + 1 >= mat1->row)
                {
                    c = 0;
                    d = 0;
                }
                if (j + 1 >= mat2->column)
                {
                    C = 0;
                    D = 0;
                }
                if (k + 1 >= mat2->row)
                {
                   B = 0;
                   D = 0; 
                }                

                u = (c - a) * (C - D);
                v = (c + d) * (C - A);
                w = (a * A) + ((c + d - a) * (A + D - C));

                *(mat_result->data + (i * mat_result->column) + j) += (a * A) + (b * B);
                *(mat_result->data + (i * mat_result->column) + (j + 1)) += w + v + ((a + b - c - d) * D);
                *(mat_result->data + ((i + 1) * mat_result->column) + j) += w + u + ((B + C - A - D) * d);
                *(mat_result->data + ((i + 1) * mat_result->column) + (j + 1)) += w + u + v;

                //printf("%d %d\n%d %d\n--------\n",a, b, c, d);
                //printf("%d %d\n%d %d\n========\n",A, C, B, D);
            }
            //printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        }
    }

    return mat_result;
}

//----------------------------------------------------

fmat* fWino(fmat* mat1, fmat* mat2)
{
    if (mat1->column != mat2->row)
    {
        perror("Dimension mismatch !\n");
        return NULL;
    }
    

    fmat* mat_result = fzeros(mat1->row, mat2->column);
    if (mat_result == NULL)
    {
        return NULL;
    }
    
    float a, b, c, d;
    a = b = c = d = 0;
    float A, B, C, D;
    A = B = C = D = 0;
    float u, v, w;
    u = v = w = 0;

    for (int i = 0; i < mat1->row; i+=2)
    {
        for (int j = 0; j < mat2->column; j+=2)
        {
            for (int k = 0; k < mat2->row; k+=2)
            {
                a = *(mat1->data + (i * mat1->column) + k);
                b = *(mat1->data + (i * mat1->column) + (k + 1));
                c = *(mat1->data + ((i + 1) * mat1->column) + k);
                d = *(mat1->data + ((i + 1) * mat1->column) + (k + 1));

                A = *(mat2->data + (k * mat2->column) + j);
                C = *(mat2->data + (k * mat2->column) + (j + 1));
                B = *(mat2->data + ((k + 1) * mat2->column) + j);
                D = *(mat2->data + ((k + 1) * mat2->column) + (j + 1));

                if (k + 1 >= mat1->column)
                {
                    b = 0;
                    d = 0;
                }
                if (i + 1 >= mat1->row)
                {
                    c = 0;
                    d = 0;
                }
                if (j + 1 >= mat2->column)
                {
                    C = 0;
                    D = 0;
                }
                if (k + 1 >= mat2->row)
                {
                   B = 0;
                   D = 0; 
                }                

                u = (c - a) * (C - D);
                v = (c + d) * (C - A);
                w = (a * A) + ((c + d - a) * (A + D - C));

                *(mat_result->data + (i * mat_result->column) + j) += (a * A) + (b * B);
                *(mat_result->data + (i * mat_result->column) + (j + 1)) += w + v + ((a + b - c - d) * D);
                *(mat_result->data + ((i + 1) * mat_result->column) + j) += w + u + ((B + C - A - D) * d);
                *(mat_result->data + ((i + 1) * mat_result->column) + (j + 1)) += w + u + v;

                //printf("%d %d\n%d %d\n--------\n",a, b, c, d);
                //printf("%d %d\n%d %d\n========\n",A, C, B, D);
            }
            //printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        }
    }

    return mat_result;
}




/*
imat* inner(imat* mat1, imat* mat2)
{
    if (mat1->column != mat2->column)
    {
        perror("Dimension mismatch \n");
        return NULL;
    }
    
    imat* mat_result = izeros(mat1->row, mat2->row);
    if (mat_result == NULL)
    {
        return NULL;
    }
    
    int column = mat1->column;

    for (int i = 0; i < mat1->row; i++)
    {
        for (int j = 0; j < mat2->row; j++)
        {
            for (int k = 0; k < column; k++)
            {
                *(mat_result->data + i * mat2->row + j) += *(mat1->data + i * mat2->row + k) * *(mat2->data + j * mat2->row + k);
            }   
        }
    }

    return mat_result;
}
*/





































