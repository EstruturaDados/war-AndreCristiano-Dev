#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// território cadastro
struct Territorio {
    char nome[50];      
    char cor[20];       
    int tropas;        
};

// Variáveis globais para o jogo
struct Territorio* mapa;
int missao_tipo;  // 1 = destruir uma cor específica, 2 = conquistar 3 territórios
char cor_jogador[20];
char cor_missao[20];  
// Função para cadastrar os 5 territórios
void cadastrar_territorios() {
    // Aloca memória  territórios
    mapa = (struct Territorio*)calloc(5, sizeof(struct Territorio));
    
    printf("=== CADASTRO DOS TERRITÓRIOS ===\n");
    printf("Vamos cadastrar 5 territórios para começar o jogo!\n\n");
    
    // Loop para cadastrar cada um dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("--- TERRITÓRIO %d ---\n", i + 1);
        
        // Pede o nome do território
        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        
        // Pede a cor do exército
        printf("Digite a cor do exército dominante: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        
        // Pede o número de tropas
        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        getchar();
        
        printf("\n");
    }
    
    // Define a cor do jogador
    printf("Agora digite SUA cor de exército (para suas conquistas): ");
    fgets(cor_jogador, sizeof(cor_jogador), stdin);
    cor_jogador[strcspn(cor_jogador, "\n")] = '\0';
    
    // Sorteia uma missão aleatória
    srand(time(NULL));
    missao_tipo = rand() % 2 + 1;
    
    if (missao_tipo == 1) {
        int territorio_aleatorio = rand() % 5;
        strcpy(cor_missao, mapa[territorio_aleatorio].cor);
    }
}

// estado atual do mapa
void mostrar_mapa() {
    printf("\n========================================\n");
    printf("           ESTADO ATUAL DO MAPA\n");
    printf("========================================\n");
    
    for (int i = 0; i < 5; i++) {
        printf("TERRITÓRIO %d:\n", i + 1);
        printf("   Nome: %s\n", mapa[i].nome);
        printf("   Exército: %s\n", mapa[i].cor);
        printf("   Tropas: %d\n", mapa[i].tropas);
        printf("----------------------------------------\n");
    }
}

// batalha entre dois territórios
void simular_batalha(int pos_atacante, int pos_defensor) {
    struct Territorio* atacante = &mapa[pos_atacante];
    struct Territorio* defensor = &mapa[pos_defensor];
    
    printf("\n=== BATALHA EM ANDAMENTO ===\n");
    printf("Atacante: %s (Exército %s) com %d tropas\n", 
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (Exército %s) com %d tropas\n", 
           defensor->nome, defensor->cor, defensor->tropas);
    
    // Simula dados de batalha (1 a 6)
    int dado_atacante = rand() % 6 + 1;
    int dado_defensor = rand() % 6 + 1;
    
    printf("\nDados lançados:\n");
    printf("Atacante rolou: %d\n", dado_atacante);
    printf("Defensor rolou: %d\n", dado_defensor);
    
    // Lógica: atacante precisa tirar MAIOR que defensor para vencer
    if (dado_atacante > dado_defensor) {
        printf("ATACANTE VENCEU!\n");
        defensor->tropas--;
        printf("%s perdeu 1 tropa. Tropas restantes: %d\n", 
               defensor->nome, defensor->tropas);
        
        // Se defensor ficou sem tropas, território é conquistado
        if (defensor->tropas == 0) {
            printf("\nTERRITÓRIO CONQUISTADO!\n");
            strcpy(defensor->cor, cor_jogador);
            defensor->tropas = 1;
            printf("%s agora pertence ao exército %s!\n", 
                   defensor->nome, defensor->cor);
        }
    } else {
        printf("DEFENSOR RESISTIU!\n");
        printf("Em caso de empate ou derrota, o defensor mantém o território.\n");
        printf("%s continua sob controle do exército %s.\n", 
               defensor->nome, defensor->cor);
    }
}

// Função para verificar se a missão foi cumprida
int verificar_missao() {
    if (missao_tipo == 1) {
        // Missão: destruir exército de uma cor específica
        for (int i = 0; i < 5; i++) {
            if (strcmp(mapa[i].cor, cor_missao) == 0) {
                return 0; // Cor ainda existe
            }
        }
        return 1; // Cor foi destruída
    } else {
        // Missão: conquistar 3 territórios
        int territorios_conquistados = 0;
        for (int i = 0; i < 5; i++) {
            if (strcmp(mapa[i].cor, cor_jogador) == 0) {
                territorios_conquistados++;
            }
        }
        return territorios_conquistados >= 3;
    }
}

// Função para mostrar a missão atual
void mostrar_missao() {
    printf("\n=== SUA MISSÃO ===\n");
    if (missao_tipo == 1) {
        printf("Destruir completamente o exército %s!\n", cor_missao);
        printf("Status: ");
        int cor_existe = 0;
        for (int i = 0; i < 5; i++) {
            if (strcmp(mapa[i].cor, cor_missao) == 0) {
                cor_existe = 1;
                break;
            }
        }
        printf("%s\n", cor_existe ? "Incompleta" : "CONCLUÍDA!");
    } else {
        printf("Conquistar pelo menos 3 territórios com seu exército %s!\n", cor_jogador);
        int conquistados = 0;
        for (int i = 0; i < 5; i++) {
            if (strcmp(mapa[i].cor, cor_jogador) == 0) {
                conquistados++;
            }
        }
        printf("Status: %d/3 territórios conquistados\n", conquistados);
        if (conquistados >= 3) {
            printf("MISSÃO CONCLUÍDA!\n");
        }
    }
}

// Função principal do jogo
void executar_ataque() {
    int atacante, defensor;
    
    printf("\nEscolha o território atacante (1-5): ");
    scanf("%d", &atacante);
    
    // Valida entrada
    if (atacante < 1 || atacante > 5) {
        printf("Território inválido!\n");
        return;
    }
    
    printf("Escolha o território defensor (1-5): ");
    scanf("%d", &defensor);
    
    // Valida entrada
    if (defensor < 1 || defensor > 5) {
        printf("Território inválido!\n");
        return;
    }
    
    if (atacante == defensor) {
        printf("Não é possível atacar o próprio território!\n");
        return;
    }
    
   
    simular_batalha(atacante - 1, defensor - 1);
}

// Menu principal do jogo
void menu_principal() {
    int opcao;
    
    do {
        printf("\n========================================\n");
        printf("              MENU PRINCIPAL\n");
        printf("========================================\n");
        printf("1 - Atacar território\n");
        printf("2 - Verificar missão\n");
        printf("3 - Mostrar mapa\n");
        printf("0 - Sair do jogo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                executar_ataque();
                break;
            case 2:
                mostrar_missao();
                if (verificar_missao()) {
                    printf("\nPARABÉNS! VOCÊ VENCEU O JOGO!\n");
                    opcao = 0; // Encerra o jogo
                }
                break;
            case 3:
                mostrar_mapa();
                break;
            case 0:
                printf("Obrigado por jogar!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        
    } while (opcao != 0);
}

// Função principal
int main() {
    printf("=== BEM-VINDO AO JOGO WAR ===\n");
    printf("Prepare-se para a conquista de territórios!\n\n");
    
    // Primeiro: cadastra os territórios
    cadastrar_territorios();
    
    // Mostra estado inicial e missão
    printf("\nCadastro concluído! O mapa está pronto para a batalha!\n");
    mostrar_mapa();
    mostrar_missao();
    
    // Inicia o menu do jogo
    menu_principal();
    
    // Libera memória alocada
    free(mapa);
    
    return 0;
}