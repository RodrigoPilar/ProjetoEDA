/*
 *  @file dados.h
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Declara as estruturas de dados utilizadas no projeto:
 *      - Antena: Armazena a frequência, coordenadas (x, y) e ponteiro para a próxima antena.
 *      - Nefasto: Armazena as coordenadas (x, y) e ponteiro para o próximo elemento.
 *      - Grafo: Armazena uma rede de antenas como grafo com lista de adjacências.
 */

#ifndef DADOS_H
#define DADOS_H

#pragma region Fase 1 : Inserção e Listagem de Antenas
 /// <summary>
 /// Estrutura que representa uma antena com frequência, coordenadas (x, y)
 /// e ponteiro para a próxima antena (lista ligada).
 /// </summary>
typedef struct antena {
    char freq;
    int x, y;
    struct antena* next;
} Antena;

/// <summary>
/// Estrutura que representa uma posição nefasto com coordenadas (x, y)
/// e ponteiro para o próximo nefasto (lista ligada).
/// </summary>
typedef struct nefasto {
    int x, y;
    struct nefasto* next;
} Nefasto;
#pragma endregion

#pragma region Fase 2 : Representação com Grafos

/// <summary>
/// Estrutura que representa uma aresta (ligação) para um vértice adjacente
/// através do índice do destino. Utiliza uma lista ligada de adjacências.
/// </summary>
typedef struct adjacente {
    int destino;
    struct adjacente* seguinte;
} Adjacente;

/// <summary>
/// Estrutura que representa um vértice do grafo, correspondente a uma antena
/// com frequência e coordenadas (x, y), e ponteiro para a sua lista de adjacentes.
/// </summary>
typedef struct {
    char freq;
    int x, y;
    Adjacente* adjacentes;
} Vertice;

/// <summary>
/// Estrutura que representa o grafo completo como uma lista de vértices,
/// com tamanho atual e vetor fixo para armazenar até 1000 vértices.
/// </summary>
typedef struct {
    int tamanho;
    Vertice vertices[1000]; // MAX_VERTICES
} Grafo;

#pragma endregion

#endif  DADOS_H
