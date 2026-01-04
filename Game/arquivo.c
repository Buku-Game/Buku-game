#include <stdio.h>
#include "arquivo.h"
#include <stdlib.h>

void iniciar (Pilha *p){
    p->topo = NULL;
}

int pilhavazia (Pilha *p){
    return p->topo == NULL;
}

void push(Pilha *p, int valor){
    No *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

int pop(Pilha *p){
    if (pilhavazia(p)){
        return -1;
    }
    No *aux = p->topo;
    int i = aux->valor;
    p->topo = aux->prox;
    free(aux);
    return i;
}

void iniciartabuleiro(Pilha t[tam][tam]){
    for (int i =0; i<tam ; i++){
        for(int j = 0; j<tam ; j++){
            iniciar(&t[i][j]);
        }
    }
}

// conta pecas na pilha
int contar_pecas(Pilha *p) {
    if (pilhavazia(p)) {
        return 0;
    }
    int count = 0;
    No *atual = p->topo;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

// verifica se casa eh branca (tipo xadrez)
bool eh_casa_branca(int linha, int coluna) {
    return (linha + coluna) % 2 == 0;
}

void liberar_pilha(Pilha *p) {
    while (!pilhavazia(p)) {
        pop(p);
    }
}

void liberar_tabuleiro(Pilha t[tam][tam]) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            liberar_pilha(&t[i][j]);
        }
    }
}

// debug - mostra tabuleiro no terminal
void imprimir_tabuleiro(Pilha t[tam][tam]) {
    printf("\n=== Tabuleiro ===\n");
    printf("   ");
    for (int j = 0; j < tam; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < tam; i++) {
        printf("%2d ", i);
        for (int j = 0; j < tam; j++) {
            int p = contar_pecas(&t[i][j]);
            if (p == 0) {
                printf(" . ");
            } else {
                printf("%2d ", p);
            }
        }
        printf("\n");
    }
    printf("=================\n");
}

int coletar_linha(Pilha t[tam][tam], int linha) {
    int total = 0;
    for (int j = 0; j < tam; j++) {
        while (!pilhavazia(&t[linha][j])) {
            pop(&t[linha][j]);
            total++;
        }
    }
    return total;
}

int coletar_coluna(Pilha t[tam][tam], int coluna) {
    int total = 0;
    for (int i = 0; i < tam; i++) {
        while (!pilhavazia(&t[i][coluna])) {
            pop(&t[i][coluna]);
            total++;
        }
    }
    return total;
}

int realizar_captura(Pilha t[tam][tam], bool turno_branco) {
    int total_cap = 0;
    
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            int num = contar_pecas(&t[i][j]);
            bool minha = (eh_casa_branca(i, j) && turno_branco) ||
                             (!eh_casa_branca(i, j) && !turno_branco);
            
            // captura casas com 3 ou 4 pecas
            if (minha && (num == 3 || num == 4)) {
                while (!pilhavazia(&t[i][j])) {
                    pop(&t[i][j]);
                    total_cap++;
                }
            }
        }
    }
    
    return total_cap;
}

bool verificar_fim_jogo(Pilha t[tam][tam]) {
    // jogo acaba quando todas casas tem no max 1 peça
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            int n = contar_pecas(&t[i][j]);
            if (n > 1) {
                return false;
            }
        }
    }
    return true;
}

void contar_pecas_restantes(Pilha t[tam][tam], int *branco, int *preto) {
    *branco = 0;
    *preto = 0;
    
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            int p = contar_pecas(&t[i][j]);
            if (eh_casa_branca(i, j)) {
                *branco += p;
            } else {
                *preto += p;
            }
        }
    }
}
