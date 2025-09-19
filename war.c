#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 20

// Definição da struct
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[MAX_TERRITORIOS]; // vetor estático
    int i;

    printf("=== Cadastro dos Territorios ===\n\n");

    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);

        printf("Nome do exército: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        printf("Cor do exército: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // remove \n

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // consumir o \n deixado pelo scanf

        printf("\n");
    }

    // Exibição do estado atual do mapa
    printf("\n=== Estado Atual do Mapa ===\n");
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome do exército: %s\n", mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Número de tropas: %d\n\n", mapa[i].tropas);
    }

    return 0;
}