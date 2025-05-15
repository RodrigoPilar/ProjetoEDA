/*
 *  @file funcoes_grafos.h
 *  @author Rodrigo Pilar
 *  @date 2025-05-13
 *  @project EDA
 *
 *  Declaração das funções utilizadas na Fase 2 do projeto (representação de grafos).
 */

#ifndef FUNCOES_GRAFOS_H
#define FUNCOES_GRAFOS_H

#include "dados.h"


void inicializarGrafo(Grafo* g);
int inserirVertice(Grafo* g, char freq, int x, int y);
void inserirAresta(Grafo* g, int origem, int destino);
void carregarGrafoDeMapa(Grafo* g, const char* ficheiro);
void listarVerticesGrafo(Grafo g);
void listarArestasGrafo(Grafo g);
int encontrarIndicePorCoordenadas(Grafo* g, int x, int y);
void dfsVisita(Grafo* g, int origem, int* visitado);
void dfsPorCoordenadas(Grafo* g, int x, int y);
void bfsVisita(Grafo* g, int origem);
void bfsPorCoordenadas(Grafo* g, int x, int y);

#endif  FUNCOES_GRAFOS_H
