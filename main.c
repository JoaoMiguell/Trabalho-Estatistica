#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tempo.h"
#include "merge.h"
#include "quick_sort.h"

#define REPETICOES 30

enum
{
    CRESCENTE,
    ALEATORIO,
    DECRESCENTE
};

const char *nomesVetores[] = {"Crescente", "Aleatorio", "Decrescente"};

void preencherVetor(int *vetor, int tamanho, int tipo)
{
    for (int i = 0; i < tamanho; i++)
    {
        switch (tipo)
        {
        case CRESCENTE:
            vetor[i] = i;
            break;

        case ALEATORIO:
            vetor[i] = rand();
            break;

        case DECRESCENTE:
            vetor[i] = tamanho - 1 - i;
            break;
        }
    }
}

int estaOrdenado(int *vetor, int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        if (vetor[i] > vetor[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

double medirMergeSort(int *vetor, int tamanho, int *aux)
{
    double inicio = obterTempo();
    MergeSort(vetor, tamanho, aux);
    double fim = obterTempo();
    return fim - inicio;
}

double medirQuickSort(int *vetor, int tamanho)
{
    double inicio = obterTempo();
    quickSort(vetor, 0, tamanho - 1);
    double fim = obterTempo();
    return fim - inicio;
}

void registrarResultado(
    FILE *arquivo,
    const char *algoritmo,
    int tamanho,
    const char *tipoVetor,
    int repeticao,
    double tempo)
{
    fprintf(arquivo,
            "%s\t%d\t%s\t%d\t%.12f\n",
            algoritmo,
            tamanho,
            tipoVetor,
            repeticao,
            tempo);
}

int main()
{
    srand((unsigned int)time(NULL));
    int tamanhos[] = {100, 1000, 10000, 100000, 1000000};
    int quantidadeTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    FILE *arquivo = fopen("resultados.tsv", "a+");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de resultados.\n");
        return 1;
    }

    fseek(arquivo, 0, SEEK_END);

    if (ftell(arquivo) == 0)
    {
        fprintf(arquivo, "Algoritmo\tTamanho\tVetor\tRepeticao\tTempo (s)\n");
    }

    for (int t = 0; t < quantidadeTamanhos; t++)
    {
        int tamanho = tamanhos[t];
        printf("\nTamanho atual: %d\n", tamanho);
        int *original = malloc(tamanho * sizeof(int));
        int *vetorMerge = malloc(tamanho * sizeof(int));
        int *vetorQuick = malloc(tamanho * sizeof(int));
        int *aux = malloc(tamanho * sizeof(int));

        if (original == NULL || vetorMerge == NULL || vetorQuick == NULL || aux == NULL)
        {
            printf("Erro ao alocar memoria.\n");
            free(original);
            free(vetorMerge);
            free(vetorQuick);
            free(aux);
            fclose(arquivo);
            return 1;
        }

        for (int tipo = CRESCENTE; tipo <= DECRESCENTE; tipo++)
        {

            printf("Vetor: %s\n", nomesVetores[tipo]);

            for (int rep = 0; rep < REPETICOES; rep++)
            {

                preencherVetor(original, tamanho, tipo);

                memcpy(vetorMerge, original, tamanho * sizeof(int));

                memcpy(vetorQuick, original, tamanho * sizeof(int));

                double tempoMerge;
                double tempoQuick;

                if (rep % 2 == 0)
                {
                    tempoMerge = medirMergeSort(vetorMerge, tamanho, aux);
                    tempoQuick = medirQuickSort(vetorQuick, tamanho);
                }
                else
                {
                    tempoQuick = medirQuickSort(vetorQuick, tamanho);
                    tempoMerge = medirMergeSort(vetorMerge, tamanho, aux);
                }

                int corretoMerge = estaOrdenado(vetorMerge, tamanho);
                int corretoQuick = estaOrdenado(vetorQuick, tamanho);

                registrarResultado(
                    arquivo,
                    "MergeSort",
                    tamanho,
                    nomesVetores[tipo],
                    rep + 1,
                    tempoMerge);

                registrarResultado(
                    arquivo,
                    "QuickSort",
                    tamanho,
                    nomesVetores[tipo],
                    rep + 1,
                    tempoQuick);

                printf("Repeticao %d/%d concluida\n",
                       rep + 1, REPETICOES);

                if (!corretoMerge || !corretoQuick)
                {
                    printf("ERRO: vetor nao ordenado corretamente!\n");
                }
            }
        }

        free(original);
        free(vetorMerge);
        free(vetorQuick);
        free(aux);
    }

    fclose(arquivo);

    printf("\nExperimentos finalizados!\n");
    printf("Resultados salvos em resultados.tsv\n");

    return 0;
}