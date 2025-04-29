#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PAISES 32
#define TAM_NOME 50

// Estrutura para armazenar os dados de cada carta (país)
typedef struct {
    char nome[TAM_NOME];
    float area;              // em km²
    unsigned long populacao; // modificador de tipo para números grandes
    float pib;               // em bilhões de dólares
    int expectativaVida;     // em anos
    float idh;               // índice de desenvolvimento humano (0 a 1)
    int codigo;              // código único da carta
} Pais;

// Variáveis globais
Pais paises[MAX_PAISES];
int totalPaises = 0;

// Protótipos das funções
void menuPrincipal();
void cadastrarPais();
void listarPaises();
void buscarPais();
void compararPaises();
void jogarPartida();
void limparBuffer();
int gerarCodigoUnico();

int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    printf("\n===== SUPER TRUNFO DE PAÍSES =====\n");
    
    // Executa o menu principal
    menuPrincipal();
    
    return 0;
}

void menuPrincipal() {
    int opcao;
    
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Cadastrar país\n");
        printf("2. Listar países cadastrados\n");
        printf("3. Buscar país por nome\n");
        printf("4. Comparar dois países\n");
        printf("5. Jogar partida\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarPais();
                break;
            case 2:
                listarPaises();
                break;
            case 3:
                buscarPais();
                break;
            case 4:
                compararPaises();
                break;
            case 5:
                jogarPartida();
                break;
            case 0:
                printf("\nObrigado por jogar! Até a próxima!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

void cadastrarPais() {
    if (totalPaises >= MAX_PAISES) {
        printf("\nLimite de países atingido! Não é possível cadastrar mais países.\n");
        return;
    }
    
    Pais novoPais;
    
    printf("\n===== CADASTRO DE PAÍS =====\n");
    
    printf("Nome do país: ");
    fgets(novoPais.nome, TAM_NOME, stdin);
    novoPais.nome[strcspn(novoPais.nome, "\n")] = '\0'; // Remove o \n do final
    
    printf("Área (km²): ");
    scanf("%f", &novoPais.area);
    
    printf("População: ");
    scanf("%lu", &novoPais.populacao);
    
    printf("PIB (bilhões de dólares): ");
    scanf("%f", &novoPais.pib);
    
    printf("Expectativa de vida (anos): ");
    scanf("%d", &novoPais.expectativaVida);
    
    printf("IDH (0 a 1): ");
    scanf("%f", &novoPais.idh);
    
    // Gera um código único para a carta
    novoPais.codigo = gerarCodigoUnico();
    
    // Adiciona o país ao array
    paises[totalPaises] = novoPais;
    totalPaises++;
    
    printf("\nPaís cadastrado com sucesso! Código da carta: %d\n", novoPais.codigo);
    
    limparBuffer();
}

void listarPaises() {
    if (totalPaises == 0) {
        printf("\nNenhum país cadastrado!\n");
        return;
    }
    
    printf("\n===== PAÍSES CADASTRADOS =====\n");
    
    for (int i = 0; i < totalPaises; i++) {
        printf("\nCarta #%d - %s\n", paises[i].codigo, paises[i].nome);
        printf("Área: %.2f km²\n", paises[i].area);
        printf("População: %lu habitantes\n", paises[i].populacao);
        printf("PIB: %.2f bilhões de dólares\n", paises[i].pib);
        printf("Expectativa de vida: %d anos\n", paises[i].expectativaVida);
        printf("IDH: %.3f\n", paises[i].idh);
        printf("---------------------------\n");
    }
}

void buscarPais() {
    if (totalPaises == 0) {
        printf("\nNenhum país cadastrado!\n");
        return;
    }
    
    char nomeBusca[TAM_NOME];
    int encontrado = 0;
    
    printf("\n===== BUSCAR PAÍS =====\n");
    printf("Digite o nome do país: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o \n do final
    
    for (int i = 0; i < totalPaises; i++) {
        // Compara strings ignorando maiúsculas/minúsculas
        if (strcasecmp(paises[i].nome, nomeBusca) == 0) {
            printf("\nPaís encontrado!\n");
            printf("\nCarta #%d - %s\n", paises[i].codigo, paises[i].nome);
            printf("Área: %.2f km²\n", paises[i].area);
            printf("População: %lu habitantes\n", paises[i].populacao);
            printf("PIB: %.2f bilhões de dólares\n", paises[i].pib);
            printf("Expectativa de vida: %d anos\n", paises[i].expectativaVida);
            printf("IDH: %.3f\n", paises[i].idh);
            
            // Cálculos adicionais usando operadores matemáticos
            float densidadeDemografica = paises[i].populacao / paises[i].area;
            float pibPerCapita = (paises[i].pib * 1000000000) / paises[i].populacao;
            
            printf("\nInformações calculadas:\n");
            printf("Densidade demográfica: %.2f hab/km²\n", densidadeDemografica);
            printf("PIB per capita: %.2f dólares\n", pibPerCapita);
            
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nPaís não encontrado!\n");
    }
}

void compararPaises() {
    if (totalPaises < 2) {
        printf("\nÉ necessário ter pelo menos 2 países cadastrados para comparação!\n");
        return;
    }
    
    int codigo1, codigo2;
    int indice1 = -1, indice2 = -1;
    
    printf("\n===== COMPARAR PAÍSES =====\n");
    
    // Lista os países disponíveis
    printf("\nPaíses disponíveis:\n");
    for (int i = 0; i < totalPaises; i++) {
        printf("%d - %s\n", paises[i].codigo, paises[i].nome);
    }
    
    printf("\nDigite o código do primeiro país: ");
    scanf("%d", &codigo1);
    
    printf("Digite o código do segundo país: ");
    scanf("%d", &codigo2);
    
    // Encontra os índices dos países pelos códigos
    for (int i = 0; i < totalPaises; i++) {
        if (paises[i].codigo == codigo1) {
            indice1 = i;
        }
        if (paises[i].codigo == codigo2) {
            indice2 = i;
        }
    }
    
    if (indice1 == -1 || indice2 == -1) {
        printf("\nUm ou ambos os códigos são inválidos!\n");
        limparBuffer();
        return;
    }
    
    // Comparação usando operadores relacionais
    printf("\n===== COMPARAÇÃO =====\n");
    printf("Comparando %s x %s\n", paises[indice1].nome, paises[indice2].nome);
    
    printf("\nÁrea:\n");
    printf("%s: %.2f km²\n", paises[indice1].nome, paises[indice1].area);
    printf("%s: %.2f km²\n", paises[indice2].nome, paises[indice2].area);
    if (paises[indice1].area > paises[indice2].area) {
        printf("Resultado: %s tem maior área\n", paises[indice1].nome);
    } else if (paises[indice1].area < paises[indice2].area) {
        printf("Resultado: %s tem maior área\n", paises[indice2].nome);
    } else {
        printf("Resultado: Empate em área\n");
    }
    
    printf("\nPopulação:\n");
    printf("%s: %lu habitantes\n", paises[indice1].nome, paises[indice1].populacao);
    printf("%s: %lu habitantes\n", paises[indice2].nome, paises[indice2].populacao);
    if (paises[indice1].populacao > paises[indice2].populacao) {
        printf("Resultado: %s tem maior população\n", paises[indice1].nome);
    } else if (paises[indice1].populacao < paises[indice2].populacao) {
        printf("Resultado: %s tem maior população\n", paises[indice2].nome);
    } else {
        printf("Resultado: Empate em população\n");
    }
    
    printf("\nPIB:\n");
    printf("%s: %.2f bilhões de dólares\n", paises[indice1].nome, paises[indice1].pib);
    printf("%s: %.2f bilhões de dólares\n", paises[indice2].nome, paises[indice2].pib);
    if (paises[indice1].pib > paises[indice2].pib) {
        printf("Resultado: %s tem maior PIB\n", paises[indice1].nome);
    } else if (paises[indice1].pib < paises[indice2].pib) {
        printf("Resultado: %s tem maior PIB\n", paises[indice2].nome);
    } else {
        printf("Resultado: Empate em PIB\n");
    }
    
    printf("\nExpectativa de vida:\n");
    printf("%s: %d anos\n", paises[indice1].nome, paises[indice1].expectativaVida);
    printf("%s: %d anos\n", paises[indice2].nome, paises[indice2].expectativaVida);
    if (paises[indice1].expectativaVida > paises[indice2].expectativaVida) {
        printf("Resultado: %s tem maior expectativa de vida\n", paises[indice1].nome);
    } else if (paises[indice1].expectativaVida < paises[indice2].expectativaVida) {
        printf("Resultado: %s tem maior expectativa de vida\n", paises[indice2].nome);
    } else {
        printf("Resultado: Empate em expectativa de vida\n");
    }
    
    printf("\nIDH:\n");
    printf("%s: %.3f\n", paises[indice1].nome, paises[indice1].idh);
    printf("%s: %.3f\n", paises[indice2].nome, paises[indice2].idh);
    if (paises[indice1].idh > paises[indice2].idh) {
        printf("Resultado: %s tem maior IDH\n", paises[indice1].nome);
    } else if (paises[indice1].idh < paises[indice2].idh) {
        printf("Resultado: %s tem maior IDH\n", paises[indice2].nome);
    } else {
        printf("Resultado: Empate em IDH\n");
    }
    
    // Cálculo de pontuação total (usando operadores matemáticos)
    int pontos1 = 0, pontos2 = 0;
    
    if (paises[indice1].area > paises[indice2].area) pontos1++;
    else if (paises[indice1].area < paises[indice2].area) pontos2++;
    
    if (paises[indice1].populacao > paises[indice2].populacao) pontos1++;
    else if (paises[indice1].populacao < paises[indice2].populacao) pontos2++;
    
    if (paises[indice1].pib > paises[indice2].pib) pontos1++;
    else if (paises[indice1].pib < paises[indice2].pib) pontos2++;
    
    if (paises[indice1].expectativaVida > paises[indice2].expectativaVida) pontos1++;
    else if (paises[indice1].expectativaVida < paises[indice2].expectativaVida) pontos2++;
    
    if (paises[indice1].idh > paises[indice2].idh) pontos1++;
    else if (paises[indice1].idh < paises[indice2].idh) pontos2++;
    
    printf("\nPontuação final:\n");
    printf("%s: %d pontos\n", paises[indice1].nome, pontos1);
    printf("%s: %d pontos\n", paises[indice2].nome, pontos2);
    
    if (pontos1 > pontos2) {
        printf("Vencedor: %s\n", paises[indice1].nome);
    } else if (pontos1 < pontos2) {
        printf("Vencedor: %s\n", paises[indice2].nome);
    } else {
        printf("Resultado: Empate\n");
    }
    
    limparBuffer();
}

void jogarPartida() {
    if (totalPaises < 2) {
        printf("\nÉ necessário ter pelo menos 2 países cadastrados para jogar!\n");
        return;
    }
    
    printf("\n===== JOGAR SUPER TRUNFO =====\n");
    printf("Regras básicas:\n");
    printf("1. Cada jogador recebe cartas aleatoriamente\n");
    printf("2. Em cada rodada, um atributo é escolhido para comparação\n");
    printf("3. O jogador com o valor mais alto no atributo escolhido vence a rodada\n");
    
    int numJogadores;
    printf("\nQuantos jogadores (2-4)? ");
    scanf("%d", &numJogadores);
    
    if (numJogadores < 2 || numJogadores > 4) {
        printf("Número de jogadores inválido! Usando 2 jogadores.\n");
        numJogadores = 2;
    }
    
    if (totalPaises < numJogadores) {
        printf("\nNão há países suficientes para distribuir entre os jogadores!\n");
        limparBuffer();
        return;
    }
    
    // Implementação simplificada - apenas mostra uma rodada de exemplo
    printf("\nSimulação de uma rodada:\n");
    
    // Seleciona dois países aleatórios
    int indice1 = rand() % totalPaises;
    int indice2;
    do {
        indice2 = rand() % totalPaises;
    } while (indice2 == indice1);
    
    printf("Jogador 1 recebeu: %s\n", paises[indice1].nome);
    printf("Jogador 2 recebeu: %s\n", paises[indice2].nome);
    
    // Seleciona um atributo aleatório
    int atributo = rand() % 5;
    char nomeAtributo[20];
    float valor1, valor2;
    
    switch(atributo) {
        case 0:
            strcpy(nomeAtributo, "Área");
            valor1 = paises[indice1].area;
            valor2 = paises[indice2].area;
            break;
        case 1:
            strcpy(nomeAtributo, "População");
            valor1 = paises[indice1].populacao;
            valor2 = paises[indice2].populacao;
            break;
        case 2:
            strcpy(nomeAtributo, "PIB");
            valor1 = paises[indice1].pib;
            valor2 = paises[indice2].pib;
            break;
        case 3:
            strcpy(nomeAtributo, "Expectativa de vida");
            valor1 = paises[indice1].expectativaVida;
            valor2 = paises[indice2].expectativaVida;
            break;
        case 4:
            strcpy(nomeAtributo, "IDH");
            valor1 = paises[indice1].idh;
            valor2 = paises[indice2].idh;
            break;
    }
    
    printf("\nAtributo sorteado: %s\n", nomeAtributo);
    printf("%s: %.2f\n", paises[indice1].nome, valor1);
    printf("%s: %.2f\n", paises[indice2].nome, valor2);
    
    if (valor1 > valor2) {
        printf("\nJogador 1 vence a rodada!\n");
    } else if (valor1 < valor2) {
        printf("\nJogador 2 vence a rodada!\n");
    } else {
        printf("\nEmpate na rodada!\n");
    }
    
    printf("\nPara um jogo completo, seria necessário implementar a distribuição de cartas\n");
    printf("e o controle de rodadas. Esta é apenas uma demonstração simplificada.\n");
    
    limparBuffer();
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int gerarCodigoUnico() {
    // Gera um código aleatório entre 1000 e 9999
    return 1000 + rand() % 9000;
}