/*
Método de Gauss

Uso do método de eliminação de Gauss 
para achar raízes de sistemas de equação lineares 
*/

#include <stdio.h>
#include <stdlib.h>

double *substituicaoRegressiva(double **m, size_t dim)
{
    double *root = (double*)malloc(dim * sizeof(double));
    double sum;
    int i,j,n;

    n = dim - 1;
    root[n] = m[n][dim]/(double)m[n][n];

    for(i = n - 1; i >= 0; i--)
    {
        sum = 0;

        for(j = i + 1; j <= n; j++ )
        {
            sum += m[i][j] * root[j];
        }

        root[i] = (m[i][dim] - sum)/(double)m[i][i];
    }
    return root;
}

void triangularSuperior(double **m, size_t dim)
{
    int i,j,k;
    double n;

    for(i = 0; i < dim; i++)
    {
        for(j = i + 1; j < dim; j++)
        {
            n = m[j][i]/(double)m[i][i];

            for(k = 0; k < dim + 1; k++)
            {
                m[j][k] = m[j][k] - n * m[i][k];
            }
        }
    }
}

double **lerMatrizCompleta(const char *arg, size_t *dim)
{
    double **m;
    int i,j;

    FILE *arq = fopen(arg,"r");

    if(arq == NULL)
    {
        printf("arquivo nao encontrado\n");
        exit(1);
    }

    fscanf(arq,"%d",dim);

    m = (double**)malloc((*dim) * sizeof(double*));

    for(i = 0; i< *dim; i++)
    {
        m[i] = (double*)malloc((*dim + 1) * sizeof(double));
    }

    for(i = 0; i < *dim; i++)
    {
        for(j = 0; j < *dim + 1; j++)
        {
            fscanf(arq,"%lf", &m[i][j]);
        }
    }
    fclose(arq);
    return m;

}

void imprimeMatrizCompleta(double **m, size_t dim)
{
    int i,j;

    for(i = 0; i < dim; i++)
    {
        for(j = 0; j < dim + 1; j++)
        {
            (j == dim)? printf("| %5.2lf\t",m[i][j]): printf("%5.2lf\t",m[i][j]);
        }
        puts("");
    }
    puts("________");
}

void imprimeRaiz(double *r, size_t dim)
{
    int i;

    puts("\n__Raízes__\n");

    for(i = 0; i < dim; i++)
    {
        printf("x[%d] = %6.3lf\n",i + 1,r[i]);
    }

    puts("________");
}

int main(int argc, char **argv)
{
    double **matriz;
    double *root;
    size_t dim;

    matriz = lerMatrizCompleta(argv[1],&dim);
    printf("MATRIX\n");
    imprimeMatrizCompleta(matriz,dim);
    triangularSuperior(matriz,dim);
    printf("\nMATRIX ESCALONADA\n");
    imprimeMatrizCompleta(matriz,dim);

    root = substituicaoRegressiva(matriz,dim);
    imprimeRaiz(root,dim);

    return 0;
}