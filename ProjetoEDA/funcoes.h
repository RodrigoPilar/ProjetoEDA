/*
 *  @file funcoes.h
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Declara as fun��es para manipula��o das listas de antenas e nefastos,al�m das fun��es para manipula��o da matriz e carregamento de uma matriz atrav�s de um ficheiro txt.
 *  
 */

#include "dados.h"

#pragma region Fun��es da Lista de Antenas
Antena* inserirAntena(Antena* lista, char freq, int x, int y);
Antena* removerAntena(Antena* lista, int x, int y);
void listarAntenas(const Antena* lista);
void libertarAntenas(Antena* lista);
#pragma endregion

#pragma region Fun��es da Lista de Nefastos
Nefasto* inserirNefasto(Nefasto* lista, int x, int y);
int existeNefasto(const Nefasto* lista, int x, int y);
Nefasto* calcularNefastos(const Antena* lista);
void listarNefastos(const Nefasto* lista);
void libertarNefastos(Nefasto* lista);
#pragma endregion

#pragma region Fun��es da Matriz
char** criarMatrizComNefastos(const Antena* listaAntenas, int* nRows, int* nCols);
void imprimirMatriz(char** matriz, int nRows);
void libertarMatriz(char** matriz, int nRows);
#pragma endregion

#pragma region Fun��es de Carregamento de Ficheiros
Antena* carregarAntenasDeFicheiro(const char* filename, Antena* listaExistente);
#pragma endregion
