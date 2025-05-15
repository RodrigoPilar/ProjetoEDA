/*
 *  @file funcoes_grafos.c
 *  @author Rodrigo Pilar
 *  @date 2025-05-13
 *  @project EDA
 *
 *  Implementação das funções da Fase 2 (grafos) do projeto.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_grafos.h"

 /// <summary>
 /// Inicializa a estrutura do grafo, definindo o tamanho como zero.
 /// </summary>
void inicializarGrafo(Grafo* g) {
    g->tamanho = 0;
}

/// <summary>
/// Insere um novo vértice (antena) no grafo com frequência e coordenadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="freq">Frequência da antena.</param>
/// <param name="x">Coordenada X.</param>
/// <param name="y">Coordenada Y.</param>
/// <returns>Índice do vértice inserido ou -1 em caso de erro.</returns>
int inserirVertice(Grafo* g, char freq, int x, int y) {
    if (g->tamanho >= 1000) return -1;

    g->vertices[g->tamanho].freq = freq;
    g->vertices[g->tamanho].x = x;
    g->vertices[g->tamanho].y = y;
    g->vertices[g->tamanho].adjacentes = NULL;

    return g->tamanho++;
}

/// <summary>
/// Insere uma ligação (aresta) entre dois vértices do grafo.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="origem">Índice do vértice de origem.</param>
/// <param name="destino">Índice do vértice de destino.</param>
void inserirAresta(Grafo* g, int origem, int destino) {
    Adjacente* novo = (Adjacente*)malloc(sizeof(Adjacente));
    novo->destino = destino;
    novo->seguinte = g->vertices[origem].adjacentes;
    g->vertices[origem].adjacentes = novo;
}

/// <summary>
/// Carrega os dados das antenas a partir de um ficheiro de texto.
/// Cada antena lida é adicionada ao grafo como vértice.
/// Ligações entre antenas com a mesma frequência são automaticamente criadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="ficheiro">Nome do ficheiro de entrada.</param>
void carregarGrafoDeMapa(Grafo* g, const char* ficheiro) {
    FILE* fp = fopen(ficheiro, "r");
    if (!fp) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    char linha[100];
    int linhaIdx = 1;

    while (fgets(linha, sizeof(linha), fp)) {
        for (int col = 0; linha[col] != '\0' && linha[col] != '\n'; col++) {
            if (linha[col] != '.') {
                inserirVertice(g, linha[col], linhaIdx, col+1);
            }
        }
        linhaIdx++;
    }

    fclose(fp);

    // Criar arestas entre antenas com a mesma frequência
    for (int i = 0; i < g->tamanho; i++) {
        for (int j = i + 1; j < g->tamanho; j++) {
            if (g->vertices[i].freq == g->vertices[j].freq) {
                inserirAresta(g, i, j);
                inserirAresta(g, j, i);
            }
        }
    }
}

/// <summary>
/// Lista todos os vértices (antenas) existentes no grafo,
/// apresentando o índice (a começar em 1), a frequência e as coordenadas (x, y).
/// </summary>
/// <param name="g">Grafo contendo os vértices (antenas).</param>
void listarVerticesGrafo(Grafo g) {
    printf("Vertices (Antenas):\n");
    for (int i = 0; i < g.tamanho; i++) {
        printf("  [%d] %c (%d, %d)\n", i + 1, g.vertices[i].freq, g.vertices[i].x, g.vertices[i].y);
    }
}

/// <summary>
/// Lista todas as arestas existentes no grafo,
/// indicando as ligações entre antenas com a mesma frequência.
/// Os índices são apresentados a começar em 1.
/// </summary>
/// <param name="g">Grafo contendo os vértices e as respetivas listas de adjacência.</param>
void listarArestasGrafo(Grafo g) {
    printf("Ligacoes (Arestas):\n");
    for (int i = 0; i < g.tamanho; i++) {
        Adjacente* adj = g.vertices[i].adjacentes;
        while (adj != NULL) {
            printf("  %d (%c) -> %d (%c)\n",
                i + 1, g.vertices[i].freq,
                adj->destino + 1, g.vertices[adj->destino].freq);
            adj = adj->seguinte;
        }
    }
}

/// <summary>
/// Procura no grafo o índice de um vértice com as coordenadas (x, y) dadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="x">Coordenada X da antena.</param>
/// <param name="y">Coordenada Y da antena.</param>
/// <returns>Índice do vértice ou -1 se não existir.</returns>
int encontrarIndicePorCoordenadas(Grafo* g, int x, int y) {
    for (int i = 0; i < g->tamanho; i++) {
        if (g->vertices[i].x == x && g->vertices[i].y == y) {
            return i;
        }
    }
    return -1;
}

/// <summary>
/// Função auxiliar recursiva para a procura em profundidade (DFS).
/// Marca vértices como visitados e imprime as suas coordenadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="atual">Índice do vértice atual.</param>
/// <param name="visitado">Array de vértices visitados.</param>
void dfsVisita(Grafo* g, int atual, int* visitado) {
    visitado[atual] = 1;
    printf("(%d, %d) - %c\n", g->vertices[atual].x, g->vertices[atual].y, g->vertices[atual].freq);

    Adjacente* adj = g->vertices[atual].adjacentes;
    while (adj != NULL) {
        if (!visitado[adj->destino]) {
            dfsVisita(g, adj->destino, visitado);
        }
        adj = adj->seguinte;
    }
}

/// <summary>
/// Realiza uma procura em profundidade (DFS) a partir de uma antena identificada pelas suas coordenadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="x">Coordenada X da antena de partida.</param>
/// <param name="y">Coordenada Y da antena de partida.</param>
void dfsPorCoordenadas(Grafo* g, int x, int y) {
    int visitado[1000] = { 0 };
    int indice = encontrarIndicePorCoordenadas(g, x, y);

    if (indice == -1) {
        printf("Antena com coordenadas (%d, %d) não encontrada.\n", x, y);
        return;
    }

    printf("DFS iniciada a partir da antena em (%d, %d):\n", x, y);
    dfsVisita(g, indice, visitado);
}

/// <summary>
/// Função auxiliar que executa a travessia em largura (BFS) a partir de um vértice.
/// Visita todos os vértices alcançáveis e imprime as respetivas coordenadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="origem">Índice do vértice de partida.</param>
void bfsVisita(Grafo* g, int origem) {
    int visitado[1000] = { 0 };
    int fila[1000];
    int inicio = 0, fim = 0;

    fila[fim++] = origem;
    visitado[origem] = 1;

    while (inicio < fim) {
        int atual = fila[inicio++];
        printf("(%d, %d) - %c\n", g->vertices[atual].x, g->vertices[atual].y, g->vertices[atual].freq);

        Adjacente* adj = g->vertices[atual].adjacentes;
        while (adj != NULL) {
            int destino = adj->destino;
            if (!visitado[destino]) {
                fila[fim++] = destino;
                visitado[destino] = 1;
            }
            adj = adj->seguinte;
        }
    }
}

/// <summary>
/// Realiza uma procura em largura (BFS) a partir de uma antena identificada pelas suas coordenadas.
/// Lista na consola as coordenadas das antenas alcançadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="x">Coordenada X da antena de partida.</param>
/// <param name="y">Coordenada Y da antena de partida.</param>
void bfsPorCoordenadas(Grafo* g, int x, int y) {
    int indice = encontrarIndicePorCoordenadas(g, x, y);

    if (indice == -1) {
        printf("Antena com coordenadas (%d, %d) não encontrada.\n", x, y);
        return;
    }

    printf("BFS iniciada a partir da antena em (%d, %d):\n", x, y);
    bfsVisita(g, indice);
}





