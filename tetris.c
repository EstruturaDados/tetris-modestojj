#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Simulação de fila de peças para Tetris Stack
// Peças com tipo ('I', 'O', 'T', 'L') e ID único

#define MAX 10

typedef struct {
    char tipo; // 'I', 'O', 'T', 'L'
    int id;    // ID único para cada peça
} Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila; // Estrutura de Fila (FIFO)

// Inicializar a fila
void iniciarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->total = 0;
}

// Verificar se fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Verificar se fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Inserir elemento no final da fila
void enqueue(Fila *f, Peca nova) {
    if (filaCheia(f)) {
        printf("\n[ERRO] Fila cheia! Nao e possivel inserir mais pecas (limite: %d).\n", MAX);
        return;
    }

    f->fim = (f->fim + 1) % MAX;
    f->itens[f->fim] = nova;
    f->total++;
    printf("\n[OK] Peca adicionada a fila - Tipo: %c, ID: %d\n", nova.tipo, nova.id);
}

// Remover elemento da frente da fila (jogar peça)
Peca dequeue(Fila *f) {
    Peca vazia = {' ', -1};

    if (filaVazia(f)) {
        printf("\n[ERRO] Fila vazia! Nao ha pecas para jogar.\n");
        return vazia;
    }

    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;

    printf("\n[OK] Peca jogada - Tipo: %c, ID: %d\n", removida.tipo, removida.id);
    return removida;
}

// Gerar peça aleatória
Peca gerarPecaAleatoria(int *contador) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;
    Peca nova = {tipos[indice], (*contador)++};
    return nova;
}

// Exibir o estado da fila
void exibirFila(Fila *f) {
    printf("\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║   FILA DE PECAS DO TETRIS STACK    ║\n");
    printf("╚════════════════════════════════════╝\n");

    if (filaVazia(f)) {
        printf("| Fila vazia! Nao ha pecas.          |\n");
    } else {
        printf("| Total de pecas: %d/%d               |\n", f->total, MAX);
        printf("|------------------------------------|\n");
        for (int i = 0; i < f->total; i++) {
            int index = (f->inicio + i) % MAX;
            printf("| [%d] Tipo: %c | ID: %2d", i + 1, f->itens[index].tipo, f->itens[index].id);
            if (i == 0) {
                printf("  <- PROXIMA A JOGAR |\n");
            } else {
                printf("             |\n");
            }
        }
    }
    printf("╚════════════════════════════════════╝\n");
}

// Menu da aplicação
void exibirMenu() {
    printf("\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║        MENU - FILA TETRIS          ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║ 1. Visualizar fila                 ║\n");
    printf("║ 2. Jogar uma peca (remover)        ║\n");
    printf("║ 3. Adicionar peca aleatoria        ║\n");
    printf("║ 4. Adicionar peca manualmente      ║\n");
    printf("║ 5. Sair                            ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf("Escolha uma opcao: ");
}

// Main
int main() {
    srand(time(NULL)); // Inicializar gerador aleatório
    Fila fila;
    iniciarFila(&fila);

    int contador_id = 1; // Contador para IDs únicos
    int opcao;

    printf("╔════════════════════════════════════╗\n");
    printf("║   BEM-VINDO AO TETRIS STACK!       ║\n");
    printf("╚════════════════════════════════════╝\n");

    // Pré-carregar algumas peças iniciais
    for (int i = 0; i < 3; i++) {
        enqueue(&fila, gerarPecaAleatoria(&contador_id));
    }
    exibirFila(&fila);

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Visualizar fila
                exibirFila(&fila);
                break;

            case 2: // Jogar uma peça (remover da frente)
                dequeue(&fila);
                exibirFila(&fila);
                break;

            case 3: // Adicionar peça aleatória
                {
                    Peca nova = gerarPecaAleatoria(&contador_id);
                    enqueue(&fila, nova);
                    exibirFila(&fila);
                }
                break;

            case 4: // Adicionar peça manualmente
                {
                    char tipo;
                    printf("\nDigite o tipo de peca (I/O/T/L): ");
                    scanf(" %c", &tipo);

                    // Validar tipo
                    if (tipo != 'I' && tipo != 'O' && tipo != 'T' && tipo != 'L') {
                        printf("[ERRO] Tipo invalido! Use I, O, T ou L.\n");
                        break;
                    }

                    Peca nova = {tipo, contador_id++};
                    enqueue(&fila, nova);
                    exibirFila(&fila);
                }
                break;

            case 5: // Sair
                printf("\n╔════════════════════════════════════╗\n");
                printf("║    Obrigado por jogar! Ate logo!   ║\n");
                printf("╚════════════════════════════════════╝\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 5.\n");
        }

    } while (opcao != 5);

    return 0;
}