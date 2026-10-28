#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define SIZE 2000000
#define REP 20

// Óo o CLOCKS_PER_SEC é constante pra obter o tempo em segundos, medir el clocks é melhor

void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;
	
	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}

void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; 

	mid = n/2; 

	L = (int*)malloc(mid*sizeof(int));
	R = (int*)malloc((n- mid)*sizeof(int));

	for(i = 0;i<mid;i++) L[i] = A[i];
	for(i = mid;i<n;i++) R[i-mid] = A[i];

	MergeSort(L,mid); 
	MergeSort(R,n-mid); 
	Merge(A,L,mid,R,n-mid); 
    free(L);
    free(R);
}

void preencheVetores(int *aleat, int *ordenado, int *inverso) {
    for (int i = 0; i < SIZE; i++) aleat[i] = rand() % SIZE;
    for (int i = 0; i < SIZE; i++) ordenado[i] = i;
    for (int i = 0; i < SIZE; i++) inverso[i] = SIZE - i;
}

int main () {
    srand(time(NULL));

    FILE *fp = fopen("resultado.txt", "w");

    int *aleat = malloc(SIZE * sizeof(int));
    int *ordenado = malloc(SIZE * sizeof(int));
    int *inverso = malloc(SIZE * sizeof(int));
    clock_t comeco, fim;
    
    fputs("MergeSort - Aleatorio: \n", fp);
    for(int i = 0; i < REP; i++) {
        preencheVetores(aleat, ordenado, inverso);
        comeco = clock();
        MergeSort(aleat, SIZE);
        fim = clock();

        printf("%d \n", fim - comeco);
        fprintf(fp, "%d\n", fim - comeco);
    }
    
    fputs("MergeSort - Ordenado: \n", fp);
    for(int i = 0; i < REP; i++) {
        preencheVetores(aleat, ordenado, inverso);
        comeco = clock();
        MergeSort(ordenado, SIZE);
        fim = clock();
        fprintf(fp, "%d\n", fim - comeco);
    }

    fputs("MergeSort - Inverso: \n", fp);
    for(int i = 0; i < REP; i++) {
        preencheVetores(aleat, ordenado, inverso);
        comeco = clock();
        MergeSort(inverso, SIZE);
        fim = clock();
        fprintf(fp, "%d\n", fim - comeco);
    }

    fclose(fp);
    free(aleat);
    free(ordenado);
    free(inverso);
}