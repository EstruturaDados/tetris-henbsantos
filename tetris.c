#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // tamanho fixo da fila
#define TAM_PILHA 3  // capacidade da pilha de reserva

// Estrutura da peça
typedef struct {
    char nome; // tipo da peça (I, O, T, L)
    int id;    // identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[TAM_FILA];
    int frente, tras, qtd;
} Fila;

// Estrutura da pilha
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// Variável global para gerar IDs únicos
int contadorID = 0;

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// Função para inicializar a pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Função que gera uma nova peça automaticamente
Peca gerarPeca() {
    Peca nova;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4]; // sorteia tipo
    nova.id = contadorID++;        // gera ID único
    return nova;
}

// Inserir peça na fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (f->qtd == TAM_FILA) {
        printf("Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->qtd++;
}

// Remover peça da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (f->qtd == 0) {
        printf("Fila vazia!\n");
        return removida;
    }
    removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    return removida;
}

// Inserir peça na pilha (push)
int push(Pilha *p, Peca x) {
    if (p->topo == TAM_PILHA - 1) {
        printf("Pilha cheia! Não é possível reservar peça.\n");
        return 0;
    }
    p->itens[++p->topo] = x;
    return 1;
}

// Remover peça da pilha (pop)
Peca pop(Pilha *p) {
    Peca removida = {'-', -1};
    if (p->topo == -1) {
        printf("Pilha vazia! Nenhuma peça reservada.\n");
        return removida;
    }
    return p->itens[p->topo--];
}

// Mostrar fila
void mostrarFila(Fila *f) {
    printf("Fila de peças:\t");
    if (f->qtd == 0) {
        printf("[vazia]");
    } else {
        int i, idx;
        for (i = 0; i < f->qtd; i++) {
            idx = (f->frente + i) % TAM_FILA;
            printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        }
    }
    printf("\n");
}

// Mostrar pilha
void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");
    if (p->topo == -1) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}

// Mostrar estado atual
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n=== Estado atual ===\n");
    mostrarFila(f);
    mostrarPilha(p);
    printf("====================\n");
}

int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;
    do {
        mostrarEstado(&fila, &pilha);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peça
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("Jogando peça: [%c %d]\n", jogada.nome, jogada.id);
                    enqueue(&fila, gerarPeca()); // mantém a fila cheia
                }
                break;
            }
            case 2: { // Reservar peça
                Peca reservada = dequeue(&fila);
                if (reservada.id != -1) {
                    if (push(&pilha, reservada)) {
                        printf("Peça reservada: [%c %d]\n", reservada.nome, reservada.id);
                        enqueue(&fila, gerarPeca()); // mantém a fila cheia
                    }
                }
                break;
            }
            case 3: { // Usar peça reservada
                Peca usada = pop(&pilha);
                if (usada.id != -1) {
                    printf("Usando peça da reserva: [%c %d]\n", usada.nome, usada.id);
                }
                break;
            }
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
