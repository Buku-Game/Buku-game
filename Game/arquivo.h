#ifndef ARQUIVO_H
#define ARQUIVO_H
#define tam 8
#include <stdbool.h>

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

// funcoes auxiliares
int contar_pecas(Pilha *p);
bool eh_casa_branca(int linha, int coluna);
void liberar_pilha(Pilha *p);
void liberar_tabuleiro(Pilha t[tam][tam]);
void imprimir_tabuleiro(Pilha t[tam][tam]);

// funcoes do jogo
int coletar_linha(Pilha t[tam][tam], int linha);
int coletar_coluna(Pilha t[tam][tam], int coluna);
int realizar_captura(Pilha t[tam][tam], bool turno_branco);
bool verificar_fim_jogo(Pilha t[tam][tam]);
void contar_pecas_restantes(Pilha t[tam][tam], int *branco, int *preto);

#endif