#include <stdio.h>
#include "merge.h"

void Merge(int *A, int *aux, int inicio, int meio, int fim)
{
    int i = inicio;
    int j = meio;
    int k = inicio;

    while (i < meio && j < fim)
    {
        if (A[i] <= A[j])
        {
            aux[k++] = A[i++];
        }
        else
        {
            aux[k++] = A[j++];
        }
    }

    while (i < meio)
    {
        aux[k++] = A[i++];
    }

    while (j < fim)
    {
        aux[k++] = A[j++];
    }

    for (i = inicio; i < fim; i++)
    {
        A[i] = aux[i];
    }
}

void MergeSortRecursivo(int *A, int *aux, int inicio, int fim)
{
    if (fim - inicio < 2)
    {
        return;
    }
    int meio = inicio + (fim - inicio) / 2;
    MergeSortRecursivo(A, aux, inicio, meio);
    MergeSortRecursivo(A, aux, meio, fim);
    Merge(A, aux, inicio, meio, fim);
}

void MergeSort(int *A, int n, int *aux)
{
    MergeSortRecursivo(A, aux, 0, n);
}