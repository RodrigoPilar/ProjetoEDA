/*
 *  @file dados.h
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Declara as estruturas de dados utilizadas no projeto:
 *      - Antena: Armazena a frequ�ncia, coordenadas (x, y) e ponteiro para a pr�xima antena.
 *      - Nefasto: Armazena as coordenadas (x, y) e ponteiro para o pr�ximo elemento.
 */

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
