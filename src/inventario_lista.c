#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventario_lista.h"

/**
 * Insere um item no início da lista encadeada
 */
void inserirItemLista(No **cabeca, int *totalItens) {
    // Aloca memória para o novo nó
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n[ERRO] Falha na alocacao de memoria!\n");
        return;
    }

    printf("\n--- ADICIONAR ITEM (LISTA) ---\n");
    
    printf("Nome do item: ");
    limparBuffer();
    fgets(novoNo->dados.nome, TAM_NOME, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';

    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(novoNo->dados.tipo, TAM_TIPO, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);

    // Insere no início da lista
    novoNo->proximo = *cabeca;
    *cabeca = novoNo;
    (*totalItens)++;

    printf("\n[SUCESSO] Item '%s' adicionado a lista!\n", novoNo->dados.nome);
}

/**
 * Remove um item da lista por nome
 */
void removerItemLista(No **cabeca, int *totalItens) {
    if (*cabeca == NULL) {
        printf("\n[AVISO] Lista vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n--- REMOVER ITEM (LISTA) ---\n");
    printf("Nome do item: ");
    limparBuffer();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    No *atual = *cabeca;
    No *anterior = NULL;

    // Busca o nó a ser removido
    while (atual != NULL && strcmp(atual->dados.nome, nomeBusca) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\n[ERRO] Item '%s' nao encontrado.\n", nomeBusca);
        return;
    }

    // Remove o nó encontrado
    if (anterior == NULL) {
        // Remove o primeiro nó
        *cabeca = atual->proximo;
    } else {
        // Remove nó do meio ou final
        anterior->proximo = atual->proximo;
    }

    printf("\n[SUCESSO] Item '%s' removido!\n", atual->dados.nome);
    free(atual);
    (*totalItens)--;
}

/**
 * Lista todos os itens da lista encadeada
 */
void listarItensLista(No *cabeca, int totalItens) {
    printf("\n========================================\n");
    printf("   ITENS NA LISTA ENCADEADA (%d)\n", totalItens);
    printf("========================================\n");

    if (cabeca == NULL) {
        printf("  [Lista vazia]\n");
        printf("========================================\n");
        return;
    }

    printf("%-20s %-15s %s\n", "NOME", "TIPO", "QTD");
    printf("----------------------------------------\n");

    No *atual = cabeca;
    while (atual != NULL) {
        printf("%-20s %-15s %d\n", 
               atual->dados.nome, 
               atual->dados.tipo, 
               atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("========================================\n");
}

/**
 * Busca sequencial na lista encadeada
 * Retorna o ponteiro para o nó encontrado ou NULL
 */
No* buscarSequencialLista(No *cabeca, char nome[], int *comparacoes) {
    *comparacoes = 0;
    No *atual = cabeca;
    
    while (atual != NULL) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}

/**
 * Libera toda a memória da lista
 */
void liberarLista(No **cabeca) {
    No *atual = *cabeca;
    No *proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    *cabeca = NULL;
}

/**
 * Menu interativo para operações com lista
 */
void menuLista(No **cabeca, int *totalItens) {
    int opcao;
    
    do {
        printf("\n======= MENU LISTA ENCADEADA =======\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (Sequencial)\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("====================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                inserirItemLista(cabeca, totalItens);
                listarItensLista(*cabeca, *totalItens);
                break;
                
            case 2:
                removerItemLista(cabeca, totalItens);
                listarItensLista(*cabeca, *totalItens);
                break;
                
            case 3:
                listarItensLista(*cabeca, *totalItens);
                break;
                
            case 4: {
                if (*cabeca == NULL) {
                    printf("\n[AVISO] Lista vazia!\n");
                    break;
                }
                
                char nomeBusca[TAM_NOME];
                printf("\nNome do item: ");
                limparBuffer();
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                
                int comparacoes = 0;
                No *no = buscarSequencialLista(*cabeca, nomeBusca, &comparacoes);
                
                if (no != NULL) {
                    printf("\n[ENCONTRADO] Busca Sequencial\n");
                    printf("  Nome: %s\n", no->dados.nome);
                    printf("  Tipo: %s\n", no->dados.tipo);
                    printf("  Quantidade: %d\n", no->dados.quantidade);
                } else {
                    printf("\n[ERRO] Item nao encontrado.\n");
                }
                printf("[INFO] Comparacoes: %d\n", comparacoes);
                break;
            }
                
            case 5:
                printf("\n[INFO] Voltando ao menu principal...\n");
                break;
                
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
        
    } while (opcao != 5);
}