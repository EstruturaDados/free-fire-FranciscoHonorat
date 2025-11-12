#ifndef TORRE_RESGATE_H
#define TORRE_RESGATE_H

#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME_COMP 30
#define TAM_TIPO_COMP 20
#define MIN_PRIORIDADE 1
#define MAX_PRIORIDADE 10

// Struct que representa um componente da torre
typedef struct {
    char nome[TAM_NOME_COMP];
    char tipo[TAM_TIPO_COMP];
    int prioridade;
} Componente;

// Struct para métricas de desempenho
typedef struct {
    int comparacoes;
    double tempoExecucao;
} Metricas;

// Enum para tipo de ordenação
typedef enum {
    ORDENACAO_NOME,
    ORDENACAO_TIPO,
    ORDENACAO_PRIORIDADE
} TipoOrdenacao;

// Funções de cadastro
void inserirComponente(Componente componentes[], int *total);
void mostrarComponentes(Componente componentes[], int total, const char *titulo);

// Algoritmos de ordenação
Metricas bubbleSortNome(Componente componentes[], int total);
Metricas insertionSortTipo(Componente componentes[], int total);
Metricas selectionSortPrioridade(Componente componentes[], int total);

// Busca binária
int buscaBinariaPorNome(Componente componentes[], int total, char nome[], int *comparacoes);

// Menu e controle
void menuTorreResgate();
void exibirMetricas(const char *nomeAlgoritmo, Metricas metricas);
void limparBufferTorre();

#endif