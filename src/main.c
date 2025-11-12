#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"
#include "inventario_vetor.h"
#include "inventario_lista.h"
#include "torre_resgate.h"

/**
 * Exibe o menu principal do sistema
 */
void exibirMenuPrincipal() {
    printf("\n========================================\n");
    printf("  FREE FIRE - SISTEMA DE INVENTARIO\n");
    printf("========================================\n");
    printf("1. Mochila com VETOR (Nivel Aventureiro)\n");
    printf("2. Mochila com LISTA (Nivel Aventureiro)\n");
    printf("3. Torre de Resgate (NIVEL MESTRE)\n");
    printf("4. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

/**
 * Função principal - Ponto de entrada do programa
 */
int main() {
    // Estruturas para vetor
    Item inventarioVetor[MAX_ITENS];
    int totalItensVetor = 0;
    
    // Estruturas para lista encadeada
    No *inventarioLista = NULL;
    int totalItensLista = 0;
    
    int opcao;

    printf("========================================\n");
    printf("  BEM-VINDO AO FREE FIRE INVENTORY\n");
    printf("     SISTEMA COMPLETO DE GESTAO\n");
    printf("========================================\n");
    printf("  Escolha seu nivel de desafio!\n");
    printf("========================================\n");

    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuVetor(inventarioVetor, &totalItensVetor);
                break;
            
            case 2:
                menuLista(&inventarioLista, &totalItensLista);
                break;
            
            case 3:
                menuTorreResgate();
                break;
            
            case 4:
                printf("\n[INFO] Liberando memoria...\n");
                liberarLista(&inventarioLista);
                printf("[INFO] Saindo do sistema...\n");
                printf("Ate a proxima, sobrevivente! 🔫🏝️\n\n");
                break;
            
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    return 0;
}