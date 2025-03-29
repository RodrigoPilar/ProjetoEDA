/*
 *  @file dados.h
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Declara as estruturas de dados utilizadas no projeto:
 *      - Antena: Armazena a frequência, coordenadas (x, y) e ponteiro para a próxima antena.
 *      - Nefasto: Armazena as coordenadas (x, y) e ponteiro para o próximo elemento.
 */

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
