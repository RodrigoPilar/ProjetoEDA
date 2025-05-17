/*
 *  @file main.c
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Implementa a função principal do programa, gerindo a inserção e listagem de antenas,
 *  o cálculo e listagem dos pontos com efeito nefasto, para além da criação e manipulação de uma matriz
 *  que combina antenas e nefastos. Também é possível carregar antenas de um ficheiro txt.
 */

#include <stdio.h>
#include "funcoes.h"
#include "funcoes_grafos.h"

int main() {
#pragma region Fase 1 : Inserção e Listagem de Antenas
       Antena* listaAntenas = NULL;
       int nRows, nCols;
       char** matriz;

       // Inserção manual de várias antenas.
       listaAntenas = inserirAntena(listaAntenas, 'A', 3, 2);
       listaAntenas = inserirAntena(listaAntenas, 'A', 5, 4);
       listaAntenas = inserirAntena(listaAntenas, 'B', 1, 1);
       listaAntenas = inserirAntena(listaAntenas, 'B', 2, 2);
       listaAntenas = inserirAntena(listaAntenas, 'C', 3, 3);
       listaAntenas = inserirAntena(listaAntenas, 'C', 15, 15);
       // Listar antenas inseridas
       listarAntenas(listaAntenas);
       // Criar e imprimir a matriz com base nas antenas inseridas
       matriz = criarMatrizComNefastos(listaAntenas, &nRows, &nCols);
       imprimirMatriz(matriz, nRows);
       libertarMatriz(matriz, nRows);

       // Remoção de antena e nova impressão da matriz para verificar se a remoção da antena da lista foi bem sucedida
       listaAntenas = removerAntena(listaAntenas, 3, 3);
       listarAntenas(listaAntenas);
       matriz = criarMatrizComNefastos(listaAntenas, &nRows, &nCols);
       imprimirMatriz(matriz, nRows);
       libertarMatriz(matriz, nRows);

       // Carregar antenas de ficheiro txt e imprimir, para verificar se a leitura do ficheiro foi bem sucedida
       listaAntenas = carregarAntenasDeFicheiro("mapa.txt", listaAntenas);
       listarAntenas(listaAntenas);
       //Criação e impressão da matriz com base nas antenas carregadas, para verificar se a lista de antenas foi bem carregada
       matriz = criarMatrizComNefastos(listaAntenas, &nRows, &nCols);
       imprimirMatriz(matriz, nRows);
       libertarMatriz(matriz, nRows);

       //Remoção de uma antena e nova impressão da matriz, para verificar se atualiza a lista de antenas carregada do ficheiro txt
       listaAntenas = removerAntena(listaAntenas, 2, 9);
       listarAntenas(listaAntenas);
       matriz = criarMatrizComNefastos(listaAntenas, &nRows, &nCols);
       imprimirMatriz(matriz, nRows);
       libertarMatriz(matriz, nRows);

       // Libertar memória antes de terminar
       libertarAntenas(listaAntenas);
#pragma endregion

#pragma region Fase 2 : Representação com Grafos
    // Inicializar grafo e carregar as antenas do ficheiro
    Grafo g;
    inicializarGrafo(&g);
    carregarGrafoDeMapa(&g, "mapa.txt");

    // Listar as antenas carregadas como vértices do grafo
    listarVerticesGrafo(g);

    // Mostrar as ligações entre as antenas com a mesma frequência
    listarArestasGrafo(g);

    // Executar uma procura em profundidade (DFS) a partir da antena com índice 0
    dfs(&g, 0);

    // Executar uma procura em largura (BFS) a partir da antena com índice 0
    bfs(&g, 0);

    // Listar todos os caminhos possíveis entre a antena 0 e a antena 3
    listarTodosOsCaminhos(&g, 0, 3);

    // Listar os pares de antenas com frequências diferentes ('A' e '0') cuja distância real entre si seja inferior ou igual a 10 unidades
    listarIntersecoesEntreFrequencias(&g, 'A', '0', 10);

#pragma endregion

    return 0;
}

