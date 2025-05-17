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
bool inserirVertice(Grafo* g, char freq, int x, int y) {
    if (g->tamanho >= 1000) return false;

    g->vertices[g->tamanho].freq = freq;
    g->vertices[g->tamanho].x = x;
    g->vertices[g->tamanho].y = y;
    g->vertices[g->tamanho].adjacentes = NULL;

    g->tamanho++;
    return true;
}

/// <summary>
/// Insere uma ligação (aresta) entre dois vértices do grafo.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="origem">Índice do vértice de origem.</param>
/// <param name="destino">Índice do vértice de destino.</param>
bool inserirAresta(Grafo* g, int origem, int destino) {
    Adjacente* novo = (Adjacente*)malloc(sizeof(Adjacente));
    if (!novo) return false;

    novo->destino = destino;
    novo->seguinte = NULL;

    Adjacente** atual = &g->vertices[origem].adjacentes;

    // Inserção ordenada por índice do destino
    while (*atual != NULL && (*atual)->destino < destino) {
        atual = &(*atual)->seguinte;
    }

    novo->seguinte = *atual;
    *atual = novo;

    return true;
}

/// <summary>
/// Cria arestas entre antenas com a mesma frequência no grafo.
/// Deve ser chamada após todos os vértices estarem inseridos.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
void criarArestasPorFrequencia(Grafo* g) {
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
/// Carrega os dados das antenas a partir de um ficheiro de texto.
/// Cada antena lida é adicionada ao grafo como vértice.
/// Ligações entre antenas com a mesma frequência são automaticamente criadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="ficheiro">Nome do ficheiro de entrada.</param>
/// <returns>True se o carregamento foi bem-sucedido; caso contrário, false.</returns>
bool carregarGrafoDeMapa(Grafo* g, const char* ficheiro) {
    FILE* fp = fopen(ficheiro, "r");
    if (!fp) {
        printf("Erro ao abrir o ficheiro.\n");
        return false;
    }

    char linha[100];
    int linhaIdx = 1;

    while (fgets(linha, sizeof(linha), fp)) {
        for (int col = 0; linha[col] != '\0' && linha[col] != '\n'; col++) {
            if (linha[col] != '.') {
                if (!inserirVertice(g, linha[col], linhaIdx, col + 1)) {
                    fclose(fp);
                    return false;
                }
            }
        }
        linhaIdx++;
    }

    fclose(fp);

    criarArestasPorFrequencia(g);
    return true;
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
/// Lista todas as arestas do grafo, organizadas por vértice,
/// mostrando claramente a que vértices está cada antena ligada.
/// </summary>
/// <param name="g">Grafo contendo os vértices e as listas de adjacência.</param>
void listarArestasGrafo(Grafo g) {
    printf("\n Ligacoes entre antenas:\n");

    for (int i = 0; i < g.tamanho; i++) {
        printf("[%d] %c (%d, %d) esta ligado a:\n", i + 1, g.vertices[i].freq, g.vertices[i].x, g.vertices[i].y);

        Adjacente* adj = g.vertices[i].adjacentes;
        if (!adj) {
            printf("   (sem ligacoes)\n");
        }

        while (adj != NULL) {
            int dest = adj->destino;
            printf("   -> [%d] %c (%d, %d)\n",
                dest + 1,
                g.vertices[dest].freq,
                g.vertices[dest].x,
                g.vertices[dest].y);
            adj = adj->seguinte;
        }

        printf("\n"); // separação entre vértices
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
/// Realiza uma procura em profundidade (DFS) a partir de um vértice do grafo (identificado pelo índice).
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="indiceOrigem">Índice do vértice de partida.</param>
void dfs(Grafo* g, int indiceOrigem) {
    int visitado[1000] = { 0 };

    if (indiceOrigem < 0 || indiceOrigem >= g->tamanho) {
        printf("Índice de vértice inválido: %d\n", indiceOrigem);
        return;
    }

    printf("DFS iniciada a partir do vértice [%d] %c (%d, %d):\n",
        indiceOrigem + 1,
        g->vertices[indiceOrigem].freq,
        g->vertices[indiceOrigem].x,
        g->vertices[indiceOrigem].y);

    dfsVisita(g, indiceOrigem, visitado);
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
/// Realiza uma procura em largura (BFS) a partir de um vértice do grafo (identificado pelo índice).
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="indiceOrigem">Índice do vértice de partida.</param>
void bfs(Grafo* g, int indiceOrigem) {
    if (indiceOrigem < 0 || indiceOrigem >= g->tamanho) {
        printf("Índice de vértice inválido: %d\n", indiceOrigem);
        return;
    }

    printf("BFS iniciada a partir do vértice [%d] %c (%d, %d):\n",
        indiceOrigem + 1,
        g->vertices[indiceOrigem].freq,
        g->vertices[indiceOrigem].x,
        g->vertices[indiceOrigem].y);

    bfsVisita(g, indiceOrigem);
}






