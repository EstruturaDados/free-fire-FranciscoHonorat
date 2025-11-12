#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventario_vetor.h"

/**
 * Insere um item no vetor
 */
void inserirItemVetor(Item inventario[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("\n[ERRO] Vetor cheio! Capacidade maxima: %d itens.\n", MAX_ITENS);
        return;
    }

    Item novoItem;
    printf("\n--- ADICIONAR ITEM (VETOR) ---\n");
    
    printf("Nome do item: ");
    limparBuffer();
    fgets(novoItem.nome, TAM_NOME, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(novoItem.tipo, TAM_TIPO, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    inventario[*totalItens] = novoItem;
    (*totalItens)++;

    printf("\n[SUCESSO] Item '%s' adicionado ao vetor!\n", novoItem.nome);
}

/**
 * Remove um item do vetor por nome
 */
void removerItemVetor(Item inventario[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\n[AVISO] Vetor vazio!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n--- REMOVER ITEM (VETOR) ---\n");
    printf("Nome do item: ");
    limparBuffer();
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        printf("\n[SUCESSO] Item '%s' removido!\n", inventario[encontrado].nome);
        
        // Desloca elementos para preencher o espaço
        for (int i = encontrado; i < *totalItens - 1; i++) {
            inventario[i] = inventario[i + 1];
        }
        (*totalItens)--;
    } else {
        printf("\n[ERRO] Item '%s' nao encontrado.\n", nomeBusca);
    }
}

/**
 * Lista todos os itens do vetor
 */
void listarItensVetor(Item inventario[], int totalItens) {
    printf("\n========================================\n");
    printf("     ITENS NO VETOR (%d/%d)\n", totalItens, MAX_ITENS);
    printf("========================================\n");

    if (totalItens == 0) {
        printf("  [Vetor vazio]\n");
        printf("========================================\n");
        return;
    }

    printf("%-20s %-15s %s\n", "NOME", "TIPO", "QTD");
    printf("----------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-20s %-15s %d\n", 
               inventario[i].nome, 
               inventario[i].tipo, 
               inventario[i].quantidade);
    }
    printf("========================================\n");
}

/**
 * Busca sequencial no vetor
 * Retorna o índice do item encontrado ou -1
 */
int buscarSequencialVetor(Item inventario[], int totalItens, char nome[], int *comparacoes) {
    *comparacoes = 0;
    
    for (int i = 0; i < totalItens; i++) {
        (*comparacoes)++;
        if (strcmp(inventario[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Ordena o vetor por nome usando Bubble Sort
 */
void ordenarVetor(Item inventario[], int totalItens, int *comparacoes) {
    *comparacoes = 0;
    
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(inventario[j].nome, inventario[j + 1].nome) > 0) {
                // Troca os itens
                Item temp = inventario[j];
                inventario[j] = inventario[j + 1];
                inventario[j + 1] = temp;
            }
        }
    }
    
    printf("\n[SUCESSO] Vetor ordenado por nome!\n");
    printf("[INFO] Comparacoes realizadas na ordenacao: %d\n", *comparacoes);
}

/**
 * Busca binária no vetor (requer vetor ordenado)
 * Retorna o índice do item encontrado ou -1
 */
int buscarBinariaVetor(Item inventario[], int totalItens, char nome[], int *comparacoes) {
    *comparacoes = 0;
    int inicio = 0;
    int fim = totalItens - 1;
    
    while (inicio <= fim) {
        (*comparacoes)++;
        int meio = inicio + (fim - inicio) / 2;
        int resultado = strcmp(inventario[meio].nome, nome);
        
        if (resultado == 0) {
            return meio; // Item encontrado
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return -1; // Item não encontrado
}

/**
 * Menu interativo para operações com vetor
 */
void menuVetor(Item inventario[], int *totalItens) {
    int opcao;
    int vetorOrdenado = 0; // Flag para controlar se está ordenado
    
    do {
        printf("\n========== MENU VETOR ==========\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (Sequencial)\n");
        printf("5. Ordenar Vetor por Nome\n");
        printf("6. Buscar Item (Binaria)\n");
        printf("7. Voltar ao Menu Principal\n");
        printf("================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                inserirItemVetor(inventario, totalItens);
                vetorOrdenado = 0; // Inserção desordena
                listarItensVetor(inventario, *totalItens);
                break;
                
            case 2:
                removerItemVetor(inventario, totalItens);
                listarItensVetor(inventario, *totalItens);
                break;
                
            case 3:
                listarItensVetor(inventario, *totalItens);
                break;
                
            case 4: {
                if (*totalItens == 0) {
                    printf("\n[AVISO] Vetor vazio!\n");
                    break;
                }
                
                char nomeBusca[TAM_NOME];
                printf("\nNome do item: ");
                limparBuffer();
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                
                int comparacoes = 0;
                int indice = buscarSequencialVetor(inventario, *totalItens, nomeBusca, &comparacoes);
                
                if (indice != -1) {
                    printf("\n[ENCONTRADO] Busca Sequencial\n");
                    printf("  Nome: %s\n", inventario[indice].nome);
                    printf("  Tipo: %s\n", inventario[indice].tipo);
                    printf("  Quantidade: %d\n", inventario[indice].quantidade);
                } else {
                    printf("\n[ERRO] Item nao encontrado.\n");
                }
                printf("[INFO] Comparacoes: %d\n", comparacoes);
                break;
            }
                
            case 5: {
                if (*totalItens == 0) {
                    printf("\n[AVISO] Vetor vazio!\n");
                    break;
                }
                
                int comparacoes = 0;
                ordenarVetor(inventario, *totalItens, &comparacoes);
                vetorOrdenado = 1;
                listarItensVetor(inventario, *totalItens);
                break;
            }
                
            case 6: {
                if (*totalItens == 0) {
                    printf("\n[AVISO] Vetor vazio!\n");
                    break;
                }
                
                if (!vetorOrdenado) {
                    printf("\n[ERRO] Vetor nao ordenado! Execute a opcao 5 primeiro.\n");
                    break;
                }
                
                char nomeBusca[TAM_NOME];
                printf("\nNome do item: ");
                limparBuffer();
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                
                int comparacoes = 0;
                int indice = buscarBinariaVetor(inventario, *totalItens, nomeBusca, &comparacoes);
                
                if (indice != -1) {
                    printf("\n[ENCONTRADO] Busca Binaria\n");
                    printf("  Nome: %s\n", inventario[indice].nome);
                    printf("  Tipo: %s\n", inventario[indice].tipo);
                    printf("  Quantidade: %d\n", inventario[indice].quantidade);
                } else {
                    printf("\n[ERRO] Item nao encontrado.\n");
                }
                printf("[INFO] Comparacoes: %d\n", comparacoes);
                break;
            }
                
            case 7:
                printf("\n[INFO] Voltando ao menu principal...\n");
                break;
                
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
        
    } while (opcao != 7);
}
