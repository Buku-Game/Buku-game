#ifndef ARQUIVO_H
#define ARQUIVO_H
#define tam 5


typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct x {
    No *topo;
} Pilha;

void iniciar(Pilha *p);
int pilhavazia(Pilha *p);
void push(Pilha *p, int valor);
int pop(Pilha *p);
void iniciartabuleiro(Pilha t[tam][tam]);


#endif