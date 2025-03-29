/*
 *  @file funcoes.c
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Implementa todas as funções para manipulação das listas de antenas e nefastos,bem como funções auxiliares para criação e manipulação da matriz.
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "funcoes.h"

#pragma region Funções da Lista de Antenas
 /// <summary>
 /// Insere uma nova antena no início da lista.
 /// </summary>
 /// <param name="lista">Lista atual de antenas.</param>
 /// <param name="freq">Frequência da nova antena.</param>
 /// <param name="x">Coordenada X da antena.</param>
 /// <param name="y">Coordenada Y da antena.</param>
 /// <returns>Nova cabeça da lista de antenas.</returns>
Antena* inserirAntena(Antena* lista, char freq, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (nova == NULL) {
        printf("Erro ao inserir nova antena.\n");
        return lista;
    }
    nova->freq = freq;
    nova->x = x;
    nova->y = y;
    nova->next = lista;
    return nova;
}

/// <summary>
/// Remove uma antena pelas suas coordenadas.
/// </summary>
/// <param name="lista">Lista atual de antenas.</param>
/// <param name="x">Coordenada X da antena a remover.</param>
/// <param name="y">Coordenada Y da antena a remover.</param>
/// <returns>Nova cabeça da lista após remoção.</returns>
Antena* removerAntena(Antena* lista, int x, int y) {
    Antena* ant = NULL;
    Antena* curr = lista;
    while (curr != NULL) {
        if (curr->x == x && curr->y == y) {
            if (ant == NULL)
                lista = curr->next;
            else
                ant->next = curr->next;
            free(curr);
            return lista;
        }
        ant = curr;
        curr = curr->next;
    }
    return lista;
}

/// <summary>
/// Lista todas as antenas presentes na lista.
/// </summary>
/// <param name="lista">Lista atual de antenas.</param>
void listarAntenas(const Antena* lista) {
    if (lista == NULL) {
        printf("\nLista de antenas vazia.\n");
        return;
    }
    printf("\nLista de Antenas\n");
    printf("Frequencia | X | Y\n");
    printf("------------------\n");
    while (lista != NULL) {
        printf("    %c     | %d | %d\n", lista->freq, lista->x, lista->y);
        lista = lista->next;
    }
}

/// <summary>
/// Liberta toda a memória da lista de antenas.
/// </summary>
/// <param name="lista">Lista de antenas a libertar.</param>
void libertarAntenas(Antena* lista) {
    Antena* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->next;
        free(temp);
    }
}
#pragma endregion

#pragma region Funções da Lista de Nefastos
/// <summary>
/// Insere um novo nefasto no início da lista.
/// </summary>
/// <param name="lista">Lista atual de nefastos.</param>
/// <param name="x">Coordenada X do nefasto.</param>
/// <param name="y">Coordenada Y do nefasto.</param>
/// <returns>Nova cabeça da lista de nefastos.</returns>
Nefasto* inserirNefasto(Nefasto* lista, int x, int y) {
    Nefasto* novo = (Nefasto*)malloc(sizeof(Nefasto));
    if (novo == NULL) {
        printf("Erro ao alocar nefasto.\n");
        return lista;
    }
    novo->x = x;
    novo->y = y;
    novo->next = lista;
    return novo;
}

/// <summary>
/// Verifica se um nefasto já existe na lista.
/// </summary>
/// <param name="lista">Lista atual de nefastos.</param>
/// <param name="x">Coordenada X.</param>
/// <param name="y">Coordenada Y.</param>
/// <returns>1 se existir, 0 caso contrário.</returns>
int existeNefasto(const Nefasto* lista, int x, int y) {
    while (lista != NULL) {
        if (lista->x == x && lista->y == y)
            return 1;
        lista = lista->next;
    }
    return 0;
}

/// <summary>
/// Calcula as posições nefastas com base nos pares de antenas da mesma frequência.
/// Para cada par (p, q) com mesma frequência, calcula os pontos simétricos L1 e L2.
/// </summary>
/// <param name="lista">Lista das antenas existentes.</param>
/// <returns>Lista de nefastos calculada.</returns>
Nefasto* calcularNefastos(const Antena* lista) {
    Nefasto* listaNefastos = NULL;
    for (const Antena* p = lista; p != NULL; p = p->next) {
        for (const Antena* q = p->next; q != NULL; q = q->next) {
            if (p->freq == q->freq) {
                // Calcula L1: ponto simétrico de p em relação a q: (2*q - p)
                int x1 = 2 * q->x - p->x;
                int y1 = 2 * q->y - p->y;
                // Calcula L2: ponto simétrico de q em relação a p: (2*p - q)
                int x2 = 2 * p->x - q->x;
                int y2 = 2 * p->y - q->y;
                // Insere na lista de nefastos se ainda não existir
                if (!existeNefasto(listaNefastos, x1, y1))
                    listaNefastos = inserirNefasto(listaNefastos, x1, y1);
                if (!existeNefasto(listaNefastos, x2, y2))
                    listaNefastos = inserirNefasto(listaNefastos, x2, y2);
            }
        }
    }
    return listaNefastos;
}

/// <summary>
/// Lista todos os nefastos presentes na lista ligada.
/// </summary>
/// <param name="lista">Lista atual de nefastos.</param>
void listarNefastos(const Nefasto* lista) {
    if (lista == NULL) {
        printf("\nLista de nefastos vazia.\n");
        return;
    }
    printf("\nLista de Nefastos\n");
    printf("X | Y\n");
    printf("--------\n");
    while (lista != NULL) {
        printf(" %d | %d\n", lista->x, lista->y);
        lista = lista->next;
    }
}

/// <summary>
/// Liberta toda a memória da lista de nefastos.
/// </summary>
/// <param name="lista">Lista de nefastos a libertar.</param>
void libertarNefastos(Nefasto* lista) {
    Nefasto* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->next;
        free(temp);  // Liberta o nó atual
    }
}
#pragma endregion

#pragma region Funções da Matriz
/// <summary>
/// Cria uma matriz que representa graficamente a localização das antenas e dos nefastos.
/// As antenas são representadas pela sua frequência (caractere),
/// e os nefastos por '#'. Espaços vazios são preenchidos com '.'.
/// </summary>
/// <param name="listaAntenas">Lista de antenas.</param>
/// <param name="listaNefastos">Lista de nefastos.</param>
/// <param name="nRows">Ponteiro para armazenar o número de linhas da matriz.</param>
/// <param name="nCols">Ponteiro para armazenar o número de colunas da matriz.</param>
/// <returns>Ponteiro para a matriz alocada dinamicamente.</returns>
char** criarMatrizComNefastos(const Antena* listaAntenas, const Nefasto* listaNefastos, int* nRows, int* nCols) {
    int minX = 100000, minY = 100000;
    int maxX = -100000, maxY = -100000;
    const Antena* auxA = listaAntenas;
    const Nefasto* auxN = listaNefastos;

    // Determina os limites mínimos e máximos com base nas antenas
    while (auxA != NULL) {
        if (auxA->x < minX) minX = auxA->x;
        if (auxA->x > maxX) maxX = auxA->x;
        if (auxA->y < minY) minY = auxA->y;
        if (auxA->y > maxY) maxY = auxA->y;
        auxA = auxA->next;
    }

    // Atualiza os limites também com base nos nefastos
    while (auxN != NULL) {
        if (auxN->x < minX) minX = auxN->x;
        if (auxN->x > maxX) maxX = auxN->x;
        if (auxN->y < minY) minY = auxN->y;
        if (auxN->y > maxY) maxY = auxN->y;
        auxN = auxN->next;
    }

    // Validação dos limites
    if (maxX < minX || maxY < minY) {
        printf("Sem dados válidos para criar a matriz.\n");
        return NULL;
    }

    // Define dimensões da matriz com base nos limites encontrados
    *nRows = maxX - minX + 1;
    *nCols = maxY - minY + 1;

    if (*nRows <= 0 || *nCols <= 0) {
        printf("Dimensões inválidas: nRows=%d, nCols=%d\n", *nRows, *nCols);
        return NULL;
    }

    // Aloca memória para a matriz
    char** matriz = malloc(*nRows * sizeof(char*));
    if (matriz == NULL) {
        printf("Erro na alocação da matriz.\n");
        exit(1);
    }

    // Inicializa cada linha da matriz com '.' e adiciona o terminador de string '\0'
    for (int i = 0; i < *nRows; i++) {
        matriz[i] = malloc((*nCols + 1) * sizeof(char)); // +1 para o '\0'
        if (matriz[i] == NULL) {
            printf("Erro na alocação da linha %d da matriz.\n", i);
            exit(1);
        }
        for (int j = 0; j < *nCols; j++) {
            matriz[i][j] = '.';
        }
        matriz[i][*nCols] = '\0';  // Permite imprimir com printf
    }

    // Coloca as antenas na matriz
    auxA = listaAntenas;
    while (auxA != NULL) {
        int linha = auxA->x - minX;
        int coluna = auxA->y - minY;
        if (linha >= 0 && linha < *nRows && coluna >= 0 && coluna < *nCols)
            matriz[linha][coluna] = auxA->freq;
        else
            printf("Antena fora dos limites: (%d, %d)\n", auxA->x, auxA->y);
        auxA = auxA->next;
    }

    // Coloca os nefastos na matriz (apenas onde não houver antena)
    auxN = listaNefastos;
    while (auxN != NULL) {
        int linha = auxN->x - minX;
        int coluna = auxN->y - minY;
        if (linha >= 0 && linha < *nRows && coluna >= 0 && coluna < *nCols) {
            if (matriz[linha][coluna] == '.')
                matriz[linha][coluna] = '#';
        }
        else {
            printf("Nefasto fora dos limites: (%d, %d)\n", auxN->x, auxN->y);
        }
        auxN = auxN->next;
    }

    return matriz;
}

/// <summary>
/// Imprime a matriz linha por linha no ecrã.
/// </summary>
/// <param name="matriz">Matriz a imprimir.</param>
/// <param name="nRows">Número de linhas da matriz.</param>
void imprimirMatriz(char** matriz, int nRows) {
    if (matriz == NULL || nRows <= 0) {
        printf("Matriz vazia ou dimensões inválidas.\n");
        return;
    }
    for (int i = 0; i < nRows; i++) {
        if (matriz[i] != NULL)
            printf("%s\n", matriz[i]);
        else
            printf("(linha %d não alocada)\n", i);
    }
}

/// <summary>
/// Liberta toda a memória alocada para a matriz.
/// </summary>
/// <param name="matriz">Matriz a libertar.</param>
/// <param name="nRows">Número de linhas da matriz.</param>
void libertarMatriz(char** matriz, int nRows) {
    if (matriz == NULL) return;
    for (int i = 0; i < nRows; i++) {
        if (matriz[i] != NULL) {
            free(matriz[i]);  // Liberta cada linha
            matriz[i] = NULL;
        }
    }
    free(matriz);  // Liberta o array de ponteiros
    matriz = NULL;
}
#pragma endregion






