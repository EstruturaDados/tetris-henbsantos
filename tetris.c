#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 5  // tamanho fixo da fila

// Estrutura da peça
typedef struct {
    char nome; // tipo da peça (I, O, T, L)
    int id;    // identificador único
} Peca;

// Estrutura da fila
typedef struct {
    Peca itens[TAMANHO];
    int frente, tras, qtd;
} Fila;

// Variável global para gerar IDs únicos
int contadorID = 0;

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// Função que gera uma nova peça automaticamente
Peca gerarPeca() {
    Peca nova;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4]; // sorteia tipo
    nova.id = contadorID++;        // gera ID único
    return nova;
}

// Inserir peça (enqueue)
void enqueue(Fila *f, Peca p) {
    if (f->qtd == TAMANHO) {
        printf("Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    f->tras = (f->tras + 1) % TAMANHO;
    f->itens[f->tras] = p;
    f->qtd++;
}

// Remover peça (dequeue)
void dequeue(Fila *f) {
    if (f->qtd == 0) {
        printf("Fila vazia! Não há peça para jogar.\n");
        return;
    }
    Peca removida = f->itens[f->frente];
    printf("Jogando peça: [%c %d]\n", removida.nome, removida.id);
    f->frente = (f->frente + 1) % TAMANHO;
    f->qtd--;
}

// Mostrar estado atual da fila
void mostrarFila(Fila *f) {
    printf("\nFila de peças:\n");
    if (f->qtd == 0) {
        printf("[vazia]\n");
        return;
    }
    int i, idx;
    for (i = 0; i < f->qtd; i++) {
        idx = (f->frente + i) % TAMANHO;
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAMANHO; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;
    do {
        mostrarFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca());
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
