// Super Trunfo de Países — Níveis: Novato, Aventureiro e Mestre
// Compilar: gcc -std=c99 -Wall -Wextra -O2 -o super_trunfo super_trunfo.c
// Executar: ./super_trunfo
//
// O programa:
// 1) Lê duas cartas (estado, código, cidade, população, área, PIB, pontos turísticos).
// 2) Calcula densidade populacional e PIB per capita de cada carta.
// 3) Calcula o "Super Poder" (soma de atributos numéricos + 1/densidade).
// 4) Compara os atributos (regra: densidade MENOR vence; demais MAIOR vence) e
//    imprime 1 quando a Carta 1 vence e 0 quando a Carta 2 vence.
//
// Observações:
// - População usa unsigned long int (para números grandes).
// - Strings com espaços (cidade) são lidas com fgets.
// - Evitamos if/else para decidir vencedores; usamos expressões relacionais.

#include <stdio.h>
#include <string.h>

#define TAM_COD   8      // margem folgada para códigos tipo "A01"
#define TAM_NOME  100    // nome da cidade

// Estrutura que representa uma carta
typedef struct {
    char estado;                    // 'A'..'H'
    char codigo[TAM_COD];           // ex: "A01"
    char cidade[TAM_NOME];          // ex: "São Paulo"
    unsigned long int populacao;    // população (não negativa)
    double area;                    // km²
    double pib;                     // em unidades monetárias (double p/ maior precisão)
    int pontos_turisticos;          // quantidade
    double densidade;               // hab/km² (derivado)
    double pib_per_capita;          // (derivado)
    double super_poder;             // (derivado)
} Carta;

// --- utilitário: remove '\n' final de fgets, se existir
static void chomp(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n-1] == '\n') s[n-1] = '\0';
}

// Lê uma carta do teclado
static void ler_carta(Carta *c, int indice) {
    printf("\n=== Cadastro da Carta %d ===\n", indice);

    // Estado (um caractere)
    printf("Estado (A-H): ");
    // Consome espaços em branco anteriores e lê 1 char
    scanf(" %c", &c->estado);

    // Código (string curta, sem espaços)
    printf("Codigo da carta (ex: A01): ");
    scanf("%7s", c->codigo);

    // Consumir newline pendente antes de fgets
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* limpa buffer */ }

    // Nome da cidade (pode ter espaços)
    printf("Nome da cidade: ");
    fgets(c->cidade, TAM_NOME, stdin);
    chomp(c->cidade);

    // Numéricos
    printf("Populacao (habitantes): ");
    scanf("%lu", &c->populacao);

    printf("Area (km^2): ");
    scanf("%lf", &c->area);

    printf("PIB (mesma unidade para as duas cartas): ");
    scanf("%lf", &c->pib);

    printf("Numero de pontos turisticos: ");
    scanf("%d", &c->pontos_turisticos);
}

// Calcula atributos derivados
static void calcular_derivados(Carta *c) {
    // Evita divisão por zero usando operador condicional
    c->densidade     = (c->area > 0.0) ? ((double)c->populacao / c->area) : 0.0;
    c->pib_per_capita= (c->populacao > 0UL) ? (c->pib / (double)c->populacao) : 0.0;

    // 1 / densidade: se densidade for 0, considera 0 para não gerar infinito
    double inv_dens  = (c->densidade > 0.0) ? (1.0 / c->densidade) : 0.0;

    // Super Poder: soma atributos numéricos principais + PIB per capita + inverso da densidade
    c->super_poder = (double)c->populacao
                   + c->area
                   + c->pib
                   + (double)c->pontos_turisticos
                   + c->pib_per_capita
                   + inv_dens;
}

// Imprime a carta formatada
static void imprimir_carta(const Carta *c, int indice) {
    printf("\nCarta %d:\n", indice);
    printf("Estado: %c\n", c->estado);
    printf("Codigo: %s\n", c->codigo);
    printf("Nome da Cidade: %s\n", c->cidade);
    printf("Populacao: %lu\n", c->populacao);
    printf("Area: %.2f km^2\n", c->area);
    printf("PIB: %.2f\n", c->pib);
    printf("Numero de Pontos Turisticos: %d\n", c->pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km^2\n", c->densidade);
    printf("PIB per Capita: %.2f\n", c->pib_per_capita);
}

// Imprime resultados das comparações (1 => Carta 1 venceu; 0 => Carta 2 venceu)
static void imprimir_comparacoes(const Carta *c1, const Carta *c2) {
    // Regras: MAIOR vence para quase todos; para DENSIDADE, MENOR vence.
    int carta1_venceu_pop   = (c1->populacao        >  c2->populacao);
    int carta1_venceu_area  = (c1->area             >  c2->area);
    int carta1_venceu_pib   = (c1->pib              >  c2->pib);
    int carta1_venceu_pts   = (c1->pontos_turisticos>  c2->pontos_turisticos);
    int carta1_venceu_dens  = (c1->densidade        <  c2->densidade); // menor vence
    int carta1_venceu_pc    = (c1->pib_per_capita   >  c2->pib_per_capita);
    int carta1_venceu_sp    = (c1->super_poder      >  c2->super_poder);

    printf("\n=== Comparacao de Cartas (1 = Carta 1 venceu; 0 = Carta 2 venceu) ===\n");
    printf("Populacao: %d\n", carta1_venceu_pop);
    printf("Area: %d\n", carta1_venceu_area);
    printf("PIB: %d\n", carta1_venceu_pib);
    printf("Pontos Turisticos: %d\n", carta1_venceu_pts);
    printf("Densidade Populacional (menor vence): %d\n", carta1_venceu_dens);
    printf("PIB per Capita: %d\n", carta1_venceu_pc);
    printf("Super Poder: %d\n", carta1_venceu_sp);
}

int main(void) {
    Carta c1 = {0}, c2 = {0};

    // Entrada de dados (nível novato)
    ler_carta(&c1, 1);
    ler_carta(&c2, 2);

    // Cálculos derivados (nível aventureiro)
    calcular_derivados(&c1);
    calcular_derivados(&c2);

    // Exibição das cartas
    imprimir_carta(&c1, 1);
    imprimir_carta(&c2, 2);

    // Cálculo do Super Poder + comparações (nível mestre)
    printf("\nSuper Poder Carta 1: %.2f\n", c1.super_poder);
    printf("Super Poder Carta 2: %.2f\n", c2.super_poder);

    imprimir_comparacoes(&c1, &c2);

    printf("\nFim.\n");
    return 0;
}
