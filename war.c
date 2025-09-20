#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 50
#define TAM_COR 20

// Definição da struct
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("Territorio %d:\n", i + 1);

        printf("Nome do exército: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // consumir o \n do scanf

        printf("\n");
    }
}

// Função para exibir o estado atual do mapa
void exibirMapa(Territorio *mapa, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome do exército: %s\n", mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Número de tropas: %d\n\n", mapa[i].tropas);
    }
}

// Função para simular uma batalha
void simularBatalha(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1; // número entre 1 e 6
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nBatalha: %s (atacante) vs %s (defensor)\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        defensor->tropas--;
        printf("%s venceu! %s perdeu 1 tropa.\n", atacante->nome, defensor->nome);

        if (defensor->tropas <= 0) {
            defensor->tropas = atacante->tropas - 1; // atacante deixa 1 tropa no território
            atacante->tropas = 1; // fica com 1 no território original
            strcpy(defensor->nome, atacante->nome);
            strcpy(defensor->cor, atacante->cor);

            printf(">>> %s conquistou o território inimigo!\n", atacante->nome);
        }
    } else {
        atacante->tropas--;
        printf("%s defendeu com sucesso! %s perdeu 1 tropa.\n", defensor->nome, atacante->nome);
    }
}

int main() {
    int n = 5;
    Territorio *mapa;

    srand(time(NULL)); // inicializa com números aleatórios

    // Alocação dinâmica
    mapa = (Territorio *)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("=== Cadastro dos Territorios ===\n\n");
    cadastrarTerritorios(mapa, n);
    exibirMapa(mapa, n);

    int opcao, atq, def;
    do {
        printf("=== Menu de Ações ===\n");
        printf("1. Realizar ataque\n");
        printf("2. Exibir mapa\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            printf("Escolha o território atacante (1 a %d): ", n);
            scanf("%d", &atq);
            getchar();
            printf("Escolha o território defensor (1 a %d): ", n);
            scanf("%d", &def);
            getchar();

            if (atq >= 1 && atq <= n && def >= 1 && def <= n && atq != def) {
                simularBatalha(&mapa[atq - 1], &mapa[def - 1]);
            } else {
                printf("Opção inválida!\n");
            }
        } else if (opcao == 2) {
            exibirMapa(mapa, n);
        }
    } while (opcao != 0);

    free(mapa); // libera memória
    return 0;
}
