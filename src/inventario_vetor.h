#ifndef INVENTARIO_VETOR_H
#define INVENTARIO_VETOR_H

#include "inventario.h"

// Funções para manipulação do vetor
void inserirItemVetor(Item inventario[], int *totalItens);
void removerItemVetor(Item inventario[], int *totalItens);
void listarItensVetor(Item inventario[], int totalItens);
int buscarSequencialVetor(Item inventario[], int totalItens, char nome[], int *comparacoes);
void ordenarVetor(Item inventario[], int totalItens, int *comparacoes);
int buscarBinariaVetor(Item inventario[], int totalItens, char nome[], int *comparacoes);
void menuVetor(Item inventario[], int *totalItens);

#endif