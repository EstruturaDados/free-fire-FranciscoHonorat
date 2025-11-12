#ifndef INVENTARIO_LISTA_H
#define INVENTARIO_LISTA_H

#include "inventario.h"

// Funções para manipulação da lista encadeada
void inserirItemLista(No **cabeca, int *totalItens);
void removerItemLista(No **cabeca, int *totalItens);
void listarItensLista(No *cabeca, int totalItens);
No* buscarSequencialLista(No *cabeca, char nome[], int *comparacoes);
void liberarLista(No **cabeca);
void menuLista(No **cabeca, int *totalItens);

#endif
