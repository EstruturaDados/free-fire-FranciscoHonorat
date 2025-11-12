#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "torre_resgate.h"

/**
 * Limpa o buffer do teclado
 */
void limparBufferTorre() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Insere um novo componente no sistema
 * @param componentes - array de componentes
 * @param total - ponteiro para o total de componentes
 */
void inserirComponente(Componente componentes[], int *total) {
    if (*total >= MAX_COMPONENTES) {
        printf("\n[ERRO] Capacidade maxima atingida! (%d componentes)\n", MAX_COMPONENTES);
        return;
    }

    Componente novo;
    
    printf("\n========================================\n");
    printf("    CADASTRAR NOVO COMPONENTE\n");
    printf("========================================\n");
    
    printf("Nome do componente: ");
    limparBufferTorre();
    fgets(novo.nome, TAM_NOME_COMP, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    
    printf("Tipo (controle/suporte/propulsao): ");
    fgets(novo.tipo, TAM_TIPO_COMP, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    
    do {
        printf("Prioridade (%d-%d): ", MIN_PRIORIDADE, MAX_PRIORIDADE);
        scanf("%d", &novo.prioridade);
        
        if (novo.prioridade < MIN_PRIORIDADE || novo.prioridade > MAX_PRIORIDADE) {
            printf("[ERRO] Prioridade invalida! Use valores entre %d e %d.\n", 
                   MIN_PRIORIDADE, MAX_PRIORIDADE);
        }
    } while (novo.prioridade < MIN_PRIORIDADE || novo.prioridade > MAX_PRIORIDADE);
    
    componentes[*total] = novo;
    (*total)++;
    
    printf("\n[SUCESSO] Componente '%s' cadastrado!\n", novo.nome);
    printf("========================================\n");
}

/**
 * Exibe todos os componentes em formato de tabela
 * @param componentes - array de componentes
 * @param total - total de componentes
 * @param titulo - título da listagem
 */
void mostrarComponentes(Componente componentes[], int total, const char *titulo) {
    printf("\n========================================\n");
    printf("  %s\n", titulo);
    printf("  Total: %d/%d componentes\n", total, MAX_COMPONENTES);
    printf("========================================\n");
    
    if (total == 0) {
        printf("  [Nenhum componente cadastrado]\n");
        printf("========================================\n");
        return;
    }
    
    printf("%-25s %-15s %s\n", "NOME", "TIPO", "PRIOR.");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < total; i++) {
        printf("%-25s %-15s %d\n", 
               componentes[i].nome,
               componentes[i].tipo,
               componentes[i].prioridade);
    }
    printf("========================================\n");
}

/**
 * Bubble Sort - Ordenação por NOME (string)
 * Complexidade: O(n²)
 * Melhor para: Dados pequenos ou quase ordenados
 * 
 * @param componentes - array a ser ordenado
 * @param total - quantidade de elementos
 * @return Metricas com comparações e tempo
 */
Metricas bubbleSortNome(Componente componentes[], int total) {
    Metricas metricas = {0, 0.0};
    clock_t inicio = clock();
    
    // Algoritmo Bubble Sort
    for (int i = 0; i < total - 1; i++) {
        int houveTroca = 0; // Otimização: detecta se array já está ordenado
        
        for (int j = 0; j < total - i - 1; j++) {
            metricas.comparacoes++;
            
            // Compara strings e troca se necessário
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                houveTroca = 1;
            }
        }
        
        // Se não houve troca, array já está ordenado
        if (!houveTroca) break;
    }
    
    clock_t fim = clock();
    metricas.tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
    
    return metricas;
}

/**
 * Insertion Sort - Ordenação por TIPO (string)
 * Complexidade: O(n²) no pior caso, O(n) no melhor
 * Melhor para: Dados pequenos ou quase ordenados
 * 
 * @param componentes - array a ser ordenado
 * @param total - quantidade de elementos
 * @return Metricas com comparações e tempo
 */
Metricas insertionSortTipo(Componente componentes[], int total) {
    Metricas metricas = {0, 0.0};
    clock_t inicio = clock();
    
    // Algoritmo Insertion Sort
    for (int i = 1; i < total; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        // Move elementos maiores uma posição à frente
        while (j >= 0) {
            metricas.comparacoes++;
            
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        
        componentes[j + 1] = chave;
    }
    
    clock_t fim = clock();
    metricas.tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
    
    return metricas;
}

/**
 * Selection Sort - Ordenação por PRIORIDADE (int)
 * Complexidade: O(n²)
 * Melhor para: Minimizar número de trocas
 * 
 * @param componentes - array a ser ordenado
 * @param total - quantidade de elementos
 * @return Metricas com comparações e tempo
 */
Metricas selectionSortPrioridade(Componente componentes[], int total) {
    Metricas metricas = {0, 0.0};
    clock_t inicio = clock();
    
    // Algoritmo Selection Sort
    for (int i = 0; i < total - 1; i++) {
        int indiceMenor = i;
        
        // Encontra o menor elemento não ordenado
        for (int j = i + 1; j < total; j++) {
            metricas.comparacoes++;
            
            if (componentes[j].prioridade < componentes[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        
        // Troca apenas se necessário
        if (indiceMenor != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[indiceMenor];
            componentes[indiceMenor] = temp;
        }
    }
    
    clock_t fim = clock();
    metricas.tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
    
    return metricas;
}

/**
 * Busca Binária por NOME
 * Complexidade: O(log n)
 * Pré-requisito: Array ordenado por nome
 * 
 * @param componentes - array ordenado
 * @param total - quantidade de elementos
 * @param nome - nome a buscar
 * @param comparacoes - ponteiro para contador
 * @return Índice do componente ou -1 se não encontrado
 */
int buscaBinariaPorNome(Componente componentes[], int total, char nome[], int *comparacoes) {
    *comparacoes = 0;
    int inicio = 0;
    int fim = total - 1;
    
    while (inicio <= fim) {
        (*comparacoes)++;
        int meio = inicio + (fim - inicio) / 2;
        int resultado = strcmp(componentes[meio].nome, nome);
        
        if (resultado == 0) {
            return meio; // Encontrado
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return -1; // Não encontrado
}

/**
 * Exibe as métricas de desempenho de um algoritmo
 * @param nomeAlgoritmo - nome do algoritmo executado
 * @param metricas - estrutura com métricas coletadas
 */
void exibirMetricas(const char *nomeAlgoritmo, Metricas metricas) {
    printf("\n+------------------------------------------+\n");
    printf("| ANALISE DE DESEMPENHO                    |\n");
    printf("+------------------------------------------+\n");
    printf("| Algoritmo:    %-27s|\n", nomeAlgoritmo);
    printf("| Comparacoes:  %-27d|\n", metricas.comparacoes);
    printf("| Tempo:        %.6f ms%16s|\n", metricas.tempoExecucao, "");
    printf("+------------------------------------------+\n");
}

/**
 * Menu principal do módulo Torre de Resgate
 * Gerencia todas as operações do sistema
 */
void menuTorreResgate() {
    Componente componentes[MAX_COMPONENTES];
    int totalComponentes = 0;
    int opcao;
    TipoOrdenacao ultimaOrdenacao = -1;
    
    printf("\n========================================\n");
    printf("    TORRE DE RESGATE - NIVEL MESTRE\n");
    printf("========================================\n");
    printf("  Missao: Organizar componentes para\n");
    printf("  construir a torre de fuga da ilha!\n");
    printf("========================================\n");
    
    do {
        printf("\n========== MENU TORRE DE RESGATE ==========\n");
        printf("1. Cadastrar Componente\n");
        printf("2. Listar Componentes\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar Componente-Chave (Busca Binaria)\n");
        printf("7. Montar Torre (Visualizar Final)\n");
        printf("8. Voltar ao Menu Principal\n");
        printf("===========================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                inserirComponente(componentes, &totalComponentes);
                ultimaOrdenacao = -1; // Desordena após inserção
                break;
                
            case 2:
                mostrarComponentes(componentes, totalComponentes, "COMPONENTES CADASTRADOS");
                break;
                
            case 3: {
                if (totalComponentes == 0) {
                    printf("\n[AVISO] Nenhum componente cadastrado!\n");
                    break;
                }
                
                printf("\n[INFO] Executando Bubble Sort por NOME...\n");
                Metricas metricas = bubbleSortNome(componentes, totalComponentes);
                exibirMetricas("Bubble Sort (Nome)", metricas);
                ultimaOrdenacao = ORDENACAO_NOME;
                mostrarComponentes(componentes, totalComponentes, "COMPONENTES ORDENADOS POR NOME");
                break;
            }
                
            case 4: {
                if (totalComponentes == 0) {
                    printf("\n[AVISO] Nenhum componente cadastrado!\n");
                    break;
                }
                
                printf("\n[INFO] Executando Insertion Sort por TIPO...\n");
                Metricas metricas = insertionSortTipo(componentes, totalComponentes);
                exibirMetricas("Insertion Sort (Tipo)", metricas);
                ultimaOrdenacao = ORDENACAO_TIPO;
                mostrarComponentes(componentes, totalComponentes, "COMPONENTES ORDENADOS POR TIPO");
                break;
            }
                
            case 5: {
                if (totalComponentes == 0) {
                    printf("\n[AVISO] Nenhum componente cadastrado!\n");
                    break;
                }
                
                printf("\n[INFO] Executando Selection Sort por PRIORIDADE...\n");
                Metricas metricas = selectionSortPrioridade(componentes, totalComponentes);
                exibirMetricas("Selection Sort (Prioridade)", metricas);
                ultimaOrdenacao = ORDENACAO_PRIORIDADE;
                mostrarComponentes(componentes, totalComponentes, "COMPONENTES ORDENADOS POR PRIORIDADE");
                break;
            }
                
            case 6: {
                if (totalComponentes == 0) {
                    printf("\n[AVISO] Nenhum componente cadastrado!\n");
                    break;
                }
                
                if (ultimaOrdenacao != ORDENACAO_NOME) {
                    printf("\n[ERRO] Para busca binaria, ordene por NOME primeiro (opcao 3)!\n");
                    printf("[DICA] A busca binaria requer dados ordenados.\n");
                    break;
                }
                
                char nomeBusca[TAM_NOME_COMP];
                printf("\n========================================\n");
                printf("    BUSCAR COMPONENTE-CHAVE\n");
                printf("========================================\n");
                printf("Nome do componente: ");
                limparBufferTorre();
                fgets(nomeBusca, TAM_NOME_COMP, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                
                int comparacoes = 0;
                int indice = buscaBinariaPorNome(componentes, totalComponentes, nomeBusca, &comparacoes);
                
                if (indice != -1) {
                    printf("\n+------------------------------------------+\n");
                    printf("| COMPONENTE-CHAVE ENCONTRADO!             |\n");
                    printf("+------------------------------------------+\n");
                    printf("| Nome:       %-29s|\n", componentes[indice].nome);
                    printf("| Tipo:       %-29s|\n", componentes[indice].tipo);
                    printf("| Prioridade: %-29d|\n", componentes[indice].prioridade);
                    printf("+------------------------------------------+\n");
                    printf("| Comparacoes: %-28d|\n", comparacoes);
                    printf("+------------------------------------------+\n");
                    printf("\n[SUCESSO] Torre destrancada! Pronta para montagem!\n");
                } else {
                    printf("\n[ERRO] Componente '%s' nao encontrado!\n", nomeBusca);
                    printf("[INFO] Comparacoes realizadas: %d\n", comparacoes);
                }
                break;
            }
                
            case 7: {
                printf("\n========================================\n");
                printf("   MONTAGEM FINAL DA TORRE DE RESGATE\n");
                printf("========================================\n");
                
                if (totalComponentes == 0) {
                    printf("[ERRO] Nenhum componente cadastrado!\n");
                    printf("Impossivel montar a torre!\n");
                } else {
                    printf("[INFO] Componentes disponiveis: %d/%d\n", 
                           totalComponentes, MAX_COMPONENTES);
                    
                    // Verifica se há componentes suficientes
                    if (totalComponentes >= 3) {
                        mostrarComponentes(componentes, totalComponentes, "COMPONENTES PARA MONTAGEM");
                        printf("\n+======================================+\n");
                        printf("| TORRE MONTADA COM SUCESSO!           |\n");
                        printf("+======================================+\n");
                        printf("| Status: OPERACIONAL                  |\n");
                        printf("| Componentes: %d                       |\n", totalComponentes);
                        printf("| Preparando para fuga da ilha... 🚀   |\n");
                        printf("+======================================+\n");
                    } else {
                        printf("\n[AVISO] Componentes insuficientes!\n");
                        printf("Minimo necessario: 3 componentes\n");
                        mostrarComponentes(componentes, totalComponentes, "COMPONENTES ATUAIS");
                    }
                }
                printf("========================================\n");
                break;
            }
                
            case 8:
                printf("\n[INFO] Voltando ao menu principal...\n");
                break;
                
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
        
    } while (opcao != 8);
}