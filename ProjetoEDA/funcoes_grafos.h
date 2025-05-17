/*
 *  @file funcoes_grafos.h
 *  @author Rodrigo Pilar
 *  @date 2025-05-13
 *  @project EDA
 *
 *  Declara��o das fun��es utilizadas na Fase 2 do projeto (representa��o de grafos).
 */

#ifndef FUNCOES_GRAFOS_H
#define FUNCOES_GRAFOS_H

#include "dados.h"
#include <stdbool.h>

void inicializarGrafo(Grafo* g);
bool inserirVertice(Grafo* g, char freq, int x, int y);
bool inserirAresta(Grafo* g, int origem, int destino);
void criarArestasPorFrequencia(Grafo* g);
bool carregarGrafoDeMapa(Grafo* g, const char* ficheiro);
void listarVerticesGrafo(Grafo g);
void listarArestasGrafo(Grafo g);
int encontrarIndicePorCoordenadas(Grafo* g, int x, int y);
void dfsVisita(Grafo* g, int origem, int* visitado);
void dfs(Grafo* g, int indiceOrigem);
void bfsVisita(Grafo* g, int origem);
void bfs(Grafo* g, int indiceOrigem);
void listarTodosOsCaminhos(Grafo* g, int origem, int destino);
void caminhosAux(Grafo* g, int atual, int destino, int* visitado, int* caminho, int profundidade);
void listarIntersecoesEntreFrequencias(Grafo* g, char freqA, char freqB, float distMax);


#endif  FUNCOES_GRAFOS_H
