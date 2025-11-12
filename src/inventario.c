#include <stdio.h>
#include "inventario.h"

/**
 * Limpa o buffer do teclado para evitar problemas com scanf
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}