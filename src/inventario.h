#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <stdbool.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// Struct que representa um item do inventário
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Struct para lista encadeada (nó)
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Funções auxiliares globais
void limparBuffer();

#endif