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
            iniciarpilha(&t[i][j]);
        }
    }
}
