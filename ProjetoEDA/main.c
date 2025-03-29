/*
 *  @file main.c
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Implementa a função principal do programa, gerindo a inserção e listagem de antenas,
 *  o cálculo e listagem dos pontos com efeito nefasto, para além da criação e manipulação de uma matriz
 *  que combina antenas e nefastos.
 */

#include <stdio.h>
#include "funcoes.h"

int main() {
    Antena* listaAntenas = NULL;
    Nefasto* listaNefastos = NULL;

    int nRows, nCols;
    int minX, minY;
    char** matriz;

    //Inserção de antenas
    listaAntenas = inserirAntena(listaAntenas, 'A', 3, 2);
    listaAntenas = inserirAntena(listaAntenas, 'A', 5, 4);
    listaAntenas = inserirAntena(listaAntenas, 'B', 1, 1);
    listaAntenas = inserirAntena(listaAntenas, 'B', 2, 2);
    listaAntenas = inserirAntena(listaAntenas, 'C', 3, 3);
	listaAntenas = inserirAntena(listaAntenas, 'C', 15, 15);
    listarAntenas(listaAntenas);

    // Remoção de uma antena e nova listagem
    listaAntenas = removerAntena(listaAntenas, 3, 3);
    listarAntenas(listaAntenas);

    // Calcula os nefastos
    listaNefastos = calcularNefastos(listaAntenas);
    listarNefastos(listaNefastos);


    // Cria a matriz combinada (insere as antenas e os nefastos)
    matriz = criarMatrizComNefastos(listaAntenas, listaNefastos, &nRows, &nCols);
    if (matriz != NULL) {
        printf("\nMatriz com antenas e nefastos:\n");
        imprimirMatriz(matriz, nRows);
        libertarMatriz(matriz, nRows);
    }
    else {
        printf("Falha na criação da matriz.\n");
    }

    // Liberta as listas
    libertarAntenas(listaAntenas);
    libertarNefastos(listaNefastos);

    return 0;
}
