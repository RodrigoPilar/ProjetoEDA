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
#include <math.h>
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
    int linhaIdx = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        for (int col = 0; linha[col] != '\0' && linha[col] != '\n'; col++) {
            if (linha[col] != '.') {
                if (!inserirVertice(g, linha[col], linhaIdx, col)) {
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
        printf("  [%d] %c (%d, %d)\n", i , g.vertices[i].freq, g.vertices[i].x, g.vertices[i].y);
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
        printf("[%d] %c (%d, %d) esta ligado a:\n", i , g.vertices[i].freq, g.vertices[i].x, g.vertices[i].y);

        Adjacente* adj = g.vertices[i].adjacentes;
        if (!adj) {
            printf("   (sem ligacoes)\n");
        }

        while (adj != NULL) {
            int dest = adj->destino;
            printf("   -> [%d] %c (%d, %d)\n",
                dest,
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
/// Função auxiliar recursiva que implementa a lógica da procura em profundidade (DFS).
/// Marca o vértice atual como visitado, imprime as suas coordenadas, e continua a travessia
/// para os vértices adjacentes não visitados.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="atual">Índice do vértice atual na travessia.</param>
/// <param name="visitado">Array que regista os vértices já visitados.</param>
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
/// Inicia a procura em profundidade (DFS) no grafo a partir de um vértice específico.
/// Mostra na consola os vértices visitados, na ordem da travessia, incluindo frequência e coordenadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="indiceOrigem">Índice do vértice de partida.</param>
void dfs(Grafo* g, int indiceOrigem) {
    int visitado[1000] = { 0 };

    if (indiceOrigem < 0 || indiceOrigem >= g->tamanho) {
        printf("Índice de vertice invalido: %d\n", indiceOrigem);
        return;
    }

    printf("DFS iniciada a partir do vertice [%d] %c (%d, %d):\n",
        indiceOrigem + 1,
        g->vertices[indiceOrigem].freq,
        g->vertices[indiceOrigem].x,
        g->vertices[indiceOrigem].y);

    dfsVisita(g, indiceOrigem, visitado);
}


/// <summary>
/// Função auxiliar que executa a travessia em largura (BFS) a partir de um vértice inicial.
/// Utiliza uma fila para visitar os vértices por níveis, imprimindo as suas coordenadas à medida que são visitados.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="origem">Índice do vértice de origem.</param>
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
/// Inicia a procura em largura (BFS) no grafo a partir de um vértice indicado.
/// Imprime os vértices visitados por ordem de nível, juntamente com as suas coordenadas e frequência.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="indiceOrigem">Índice do vértice de origem.</param>
void bfs(Grafo* g, int indiceOrigem) {
    if (indiceOrigem < 0 || indiceOrigem >= g->tamanho) {
        printf("Índice de vertice invalido: %d\n", indiceOrigem);
        return;
    }

    printf("BFS iniciada a partir do vertice [%d] %c (%d, %d):\n",
        indiceOrigem + 1,
        g->vertices[indiceOrigem].freq,
        g->vertices[indiceOrigem].x,
        g->vertices[indiceOrigem].y);

    bfsVisita(g, indiceOrigem);
}

/// <summary>
/// Função recursiva auxiliar que identifica todos os caminhos possíveis entre dois vértices do grafo.
/// A travessia é feita com backtracking, garantindo que não há ciclos e que todos os caminhos válidos são explorados.
/// Quando um caminho é encontrado, é imediatamente impresso na consola.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="atual">Índice do vértice atual no caminho.</param>
/// <param name="destino">Índice do vértice de destino.</param>
/// <param name="visitado">Array que assinala os vértices já visitados no caminho atual.</param>
/// <param name="caminho">Array que guarda os índices do caminho atual.</param>
/// <param name="profundidade">Número de vértices visitados no caminho atual.</param>
void caminhosAux(Grafo* g, int atual, int destino, int* visitado, int* caminho, int profundidade) {
    visitado[atual] = 1;
    caminho[profundidade] = atual;

    if (atual == destino) {
        // Caminho completo encontrado: imprimir
        printf("Caminho encontrado:\n");
        for (int i = 0; i <= profundidade; i++) {
            int idx = caminho[i];
            printf("  [%d] %c (%d, %d)\n", idx + 1, g->vertices[idx].freq, g->vertices[idx].x, g->vertices[idx].y);
        }
        printf("\n");
    }
    else {
        Adjacente* adj = g->vertices[atual].adjacentes;
        while (adj != NULL) {
            if (!visitado[adj->destino]) {
                caminhosAux(g, adj->destino, destino, visitado, caminho, profundidade + 1);
            }
            adj = adj->seguinte;
        }
    }

    // Backtrack
    visitado[atual] = 0;
}

/// <summary>
/// Lista todos os caminhos possíveis entre dois vértices no grafo, identificados pelos seus índices.
/// Para cada caminho encontrado, imprime a sequência completa de vértices visitados, com frequência e coordenadas.
/// Esta função recorre à função auxiliar recursiva para realizar a travessia completa com backtracking.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="origem">Índice do vértice de origem.</param>
/// <param name="destino">Índice do vértice de destino.</param>
void listarTodosOsCaminhos(Grafo* g, int origem, int destino) {
    if (origem < 0 || origem >= g->tamanho || destino < 0 || destino >= g->tamanho) {
        printf("\nIndices invalidos para origem ou destino.");
        return;
    }

    int visitado[1000] = { 0 };
    int caminho[1000];

    printf("\nTodos os caminhos de [%d] %c (%d, %d) para [%d] %c (%d, %d):\n",
        origem, g->vertices[origem].freq, g->vertices[origem].x, g->vertices[origem].y,
        destino, g->vertices[destino].freq, g->vertices[destino].x, g->vertices[destino].y);

    caminhosAux(g, origem, destino, visitado, caminho, 0);
}

/// <summary>
/// Lista todos os pares possíveis entre antenas de duas frequências distintas,
/// cuja distância euclidiana entre si seja menor ou igual ao valor fornecido.
/// Para cada par válido, apresenta as coordenadas das duas antenas associadas.
/// </summary>
/// <param name="g">Ponteiro para o grafo.</param>
/// <param name="freqA">Primeira frequência.</param>
/// <param name="freqB">Segunda frequência.</param>
/// <param name="distMax">Distância máxima permitida entre as antenas.</param>
void listarIntersecoesEntreFrequencias(Grafo* g, char freqA, char freqB, float distMax) {
    printf("\nIntersecoes entre antenas de frequencia '%c' e '%c' com distancia <= %.2f:\n\n", freqA, freqB, distMax);

    for (int i = 0; i < g->tamanho; i++) {
        if (g->vertices[i].freq == freqA) {
            for (int j = 0; j < g->tamanho; j++) {
                if (g->vertices[j].freq == freqB) {
                    int dx = g->vertices[i].x - g->vertices[j].x;
                    int dy = g->vertices[i].y - g->vertices[j].y;
                    float dist = sqrt((float)(dx * dx + dy * dy));

                    if (dist <= distMax) {
                        printf("[%c] (%d, %d) <-> [%c] (%d, %d) | Distancia: %.2f\n",
                            freqA, g->vertices[i].x, g->vertices[i].y,
                            freqB, g->vertices[j].x, g->vertices[j].y,
                            dist);
                    }
                }
            }
        }
    }
}






