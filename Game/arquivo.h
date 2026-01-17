#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdbool.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct Nodiescritor {
    No *topo;
    int size;
} Pilha;


//fucoes principais
void iniciar(Pilha *p);
int pilhavazia(Pilha *p);
void push(Pilha *p, int valor);
int pop(Pilha *p);
void iniciartabuleiro(Pilha ***t, int n);

// funcoes auxiliares
int contar_pecas(Pilha *p);
bool eh_casa_branca(int linha, int coluna);
void liberar_pilha(Pilha *p);
void liberar_tabuleiro(Pilha **t, int tam);
void imprimir_tabuleiro(Pilha **t, int tam);

// funcoes do jogo
int coletar_linha(Pilha **t, int linha, int tam);
int coletar_coluna(Pilha **t, int coluna, int tam);
int realizar_captura(Pilha **t, bool turno_branco, int tam);
bool verificar_fim_jogo(Pilha **t, int tam);
void contar_pecas_restantes(Pilha **t, int *branco, int *preto, int tam);
void push_pecas(Pilha *p, int i);

#endif