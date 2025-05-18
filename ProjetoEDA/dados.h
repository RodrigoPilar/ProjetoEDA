/*
 *  @file dados.h
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 * 
 * Declara as estruturas de dados utilizadas no projeto:
 *
 * Fase 1:
 *  - Antena: Armazena a frequ�ncia, coordenadas (x, y) e ponteiro para a pr�xima antena.
 *  - Nefasto: Armazena coordenadas de efeitos nefastos e ponteiro para o pr�ximo.
 *
 * Fase 2:
 *  - Adjacente: Representa uma liga��o entre v�rtices no grafo.
 *  - Vertice: Representa uma antena com lista de adjacentes.
 *  - Grafo: Cont�m todos os v�rtices (antenas) e respetivas liga��es.
 */

#ifndef DADOS_H
#define DADOS_H

#pragma region Fase 1 : Inser��o e Listagem de Antenas
 /// <summary>
 /// Estrutura que representa uma antena com frequ�ncia, coordenadas (x, y)
 /// e ponteiro para a pr�xima antena (lista ligada).
 /// </summary>
typedef struct antena {
    char freq;
    int x, y;
    struct antena* next;
} Antena;

/// <summary>
/// Estrutura que representa uma posi��o nefasto com coordenadas (x, y)
/// e ponteiro para o pr�ximo nefasto (lista ligada).
/// </summary>
typedef struct nefasto {
    int x, y;
    struct nefasto* next;
} Nefasto;
#pragma endregion

#pragma region Fase 2 : Representa��o com Grafos

/// <summary>
/// Estrutura que representa uma aresta (liga��o) para um v�rtice adjacente
/// atrav�s do �ndice do destino. Utiliza uma lista ligada de adjac�ncias.
/// </summary>
typedef struct adjacente {
    int destino;
    struct adjacente* seguinte;
} Adjacente;

/// <summary>
/// Estrutura que representa um v�rtice do grafo, correspondente a uma antena
/// com frequ�ncia e coordenadas (x, y), e ponteiro para a sua lista de adjacentes.
/// </summary>
typedef struct {
    char freq;
    int x, y;
    Adjacente* adjacentes;
} Vertice;

/// <summary>
/// Estrutura que representa o grafo completo como uma lista de v�rtices,
/// com tamanho atual e vetor fixo para armazenar at� 1000 v�rtices.
/// </summary>
typedef struct {
    int tamanho;
    Vertice vertices[1000]; // MAX_VERTICES
} Grafo;

#pragma endregion

#endif  // DADOS_H
