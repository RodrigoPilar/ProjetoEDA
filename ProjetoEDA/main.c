/*
 *  @file main.c
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Implementa a fun��o principal do programa, demonstrando as funcionalidades*  desenvolvidas nas duas fases do projeto EDA:
 * 
 *  - Fase 1: Inser��o, listagem e remo��o de antenas, c�lculo de pontos com efeito nefasto e manipula��o de uma matriz que representa o mapa.
 *  - Fase 2: Representa��o das antenas num grafo com lista de adjac�ncias, travessias DFS/BFS,listagem de todos os caminhos poss�veis entre antenas e interse��es com base na dist�ncia entre antenas de frequ�ncias distintas.
 *            
 *          
 */

#include <stdio.h>
#include "funcoes.h"
#include "funcoes_grafos.h"


// Demonstra��o completa das funcionalidades da Fase 1 e Fase 2 do projeto EDA
int main() {
#pragma region Fase 1 : Inser��o e Listagem de Antenas
       Antena* listaAntenas = NULL;
       int nRows, nCols;
       char** matriz;

       // Inser��o manual de v�rias antenas.
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

       // Remo��o de antena e nova impress�o da matriz para verificar se a remo��o da antena da lista foi bem sucedida
       listaAntenas = removerAntena(listaAntenas, 3, 3);
       listarAntenas(listaAntenas);
       matriz = criarMatrizComNefastos(listaAntenas, &nRows, &nCols);
       imprimirMatriz(matriz, nRows);
       libertarMatriz(matriz, nRows);

       // Carregar antenas de ficheiro txt e imprimir, para verificar se a leitura do ficheiro foi bem sucedida
       listaAntenas = carregarAntenasDeFicheiro("mapa.txt", listaAntenas);
       listarAntenas(listaAntenas);
       //Cria��o e impress�o da matriz com base nas antenas carregadas, para verificar se a lista de antenas foi bem carregada
       matriz = criarMatrizComNefastos(listaAntenas, &nRows, &nCols);
       imprimirMatriz(matriz, nRows);
       libertarMatriz(matriz, nRows);

       //Remo��o de uma antena e nova impress�o da matriz, para verificar se atualiza a lista de antenas carregada do ficheiro txt
       listaAntenas = removerAntena(listaAntenas, 2, 9);
       listarAntenas(listaAntenas);
       matriz = criarMatrizComNefastos(listaAntenas, &nRows, &nCols);
       imprimirMatriz(matriz, nRows);
       libertarMatriz(matriz, nRows);

       // Libertar mem�ria antes de terminar
       libertarAntenas(listaAntenas);
#pragma endregion

#pragma region Fase 2 : Representa��o com Grafos
    // Inicializar grafo e carregar as antenas do ficheiro
    Grafo g;
    inicializarGrafo(&g);
    carregarGrafoDeMapa(&g, "mapa.txt");

    // Listar as antenas carregadas como v�rtices do grafo
    listarVerticesGrafo(g);

    // Mostrar as liga��es entre as antenas com a mesma frequ�ncia
    listarArestasGrafo(g);

    // Executar uma procura em profundidade (DFS) a partir da antena com �ndice 0
    dfs(&g, 0);

    // Executar uma procura em largura (BFS) a partir da antena com �ndice 0
    bfs(&g, 0);

    // Listar todos os caminhos poss�veis entre a antena 0 e a antena 3
    listarTodosOsCaminhos(&g, 0, 3);

    // Listar os pares de antenas com frequ�ncias diferentes ('A' e '0') cuja dist�ncia real entre si seja inferior ou igual a 10 unidades
    listarIntersecoesEntreFrequencias(&g, 'A', '0', 10);

#pragma endregion

    return 0;
}

