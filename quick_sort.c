#include <stdio.h>
#include <stdlib.h>
#include "quick_sort.h"

void swap(int *a, int *b)
{

    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high)
{
    int posicaoAleatoria = low + rand() % (high - low + 1);
    swap(&arr[posicaoAleatoria], &arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    while (low < high)
    {
        int pi = partition(arr, low, high);
        if (pi - low < high - pi)
        {

            quickSort(arr, low, pi - 1);
            low = pi + 1;
        }
        else
        {

            quickSort(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}