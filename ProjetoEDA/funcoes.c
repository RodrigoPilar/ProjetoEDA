/*
 *  @file funcoes.c
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Implementa todas as funções para manipulação das listas de antenas e nefastos,bem como funções auxiliares para criação, manipulação da matriz e carregamento de uma matriz através de um ficheiro txt.
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "funcoes.h"

#pragma region Funções da Lista de Antenas

 /// <summary>
 /// Insere uma nova antena no início da lista ligada.
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
    nova->next = lista; // Aponta para o antigo início da lista
    return nova;
}

/// <summary>
/// Remove uma antena da lista com base nas suas coordenadas.
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
                lista = curr->next; // A antena a remover é a primeira da lista
            else
                ant->next = curr->next; // Liga o anterior ao seguinte, removendo o atual
            free(curr);
            return lista;
        }
        ant = curr;
        curr = curr->next;
    }
    return lista; 
}

/// <summary>
/// Imprime todas as antenas da lista no ecrã de forma tabular.
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
/// Liberta toda a memória ocupada pela lista de antenas.
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
/// Insere um novo nefasto no início da lista ligada.
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
/// Verifica se uma determinada posição nefasto já existe na lista.
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
/// Calcula e cria a lista de posições nefastas a partir de pares de antenas com a mesma frequência.
/// </summary>
/// <param name="lista">Lista de antenas existentes.</param>
/// <returns>Lista de nefastos calculada com base nas simetrias.</returns>
Nefasto* calcularNefastos(const Antena* lista) {
    Nefasto* listaNefastos = NULL;
    for (const Antena* p = lista; p != NULL; p = p->next) {
        for (const Antena* q = p->next; q != NULL; q = q->next) {
            if (p->freq == q->freq) {
                // Calcula o ponto simétrico de p em relação a q
                int x1 = 2 * q->x - p->x;
                int y1 = 2 * q->y - p->y;
                // Calcula o ponto simétrico de q em relação a p
                int x2 = 2 * p->x - q->x;
                int y2 = 2 * p->y - q->y;
                // Apenas insere se não existir ainda na lista
                if (!existeNefasto(listaNefastos, x1, y1))
                    listaNefastos = inserirNefasto(listaNefastos, x1, y1);
                if (!existeNefasto(listaNefastos, x2, y2))
                    listaNefastos = inserirNefasto(listaNefastos, x2, y2);
            }
        }
    }
    listarNefastos(listaNefastos); // Apresenta os nefastos calculados
    return listaNefastos;
}

/// <summary>
/// Lista todos os nefastos presentes na lista ligada no ecrã.
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
/// Liberta da memória todos os elementos da lista de nefastos.
/// </summary>
/// <param name="lista">Lista de nefastos a libertar.</param>
void libertarNefastos(Nefasto* lista) {
    Nefasto* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->next;
        free(temp);
    }
}

#pragma endregion

#pragma region Funções da Matriz

/// <summary>
/// Cria uma matriz que representa graficamente a localização das antenas e dos nefastos.
/// As antenas são representadas pela sua frequência (letra), os nefastos por '#' e os restantes espaços por '.'.
/// </summary>
/// <param name="listaAntenas">Lista de antenas.</param>
/// <param name="nRows">Ponteiro onde será guardado o número de linhas da matriz.</param>
/// <param name="nCols">Ponteiro onde será guardado o número de colunas da matriz.</param>
/// <returns>Ponteiro para a matriz criada dinamicamente.</returns>
char** criarMatrizComNefastos(const Antena* listaAntenas, int* nRows, int* nCols) {
    if (!listaAntenas) {
        printf("Lista de antenas vazia. Sem dados para criar a matriz.\n");
        return NULL;
    }

    // Calcula os pontos nefastos a partir da lista de antenas fornecida
    Nefasto* listaNefastos = calcularNefastos(listaAntenas);

    // Determina os limites da matriz com base nas posições de antenas e nefastos
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;

    // Atualiza os limites mínimos e máximos com base nas antenas
    for (const Antena* a = listaAntenas; a; a = a->next) {
        if (a->x < minX) minX = a->x;
        if (a->x > maxX) maxX = a->x;
        if (a->y < minY) minY = a->y;
        if (a->y > maxY) maxY = a->y;
    }

    // Atualiza também com base nos nefastos
    for (const Nefasto* n = listaNefastos; n; n = n->next) {
        if (n->x < minX) minX = n->x;
        if (n->x > maxX) maxX = n->x;
        if (n->y < minY) minY = n->y;
        if (n->y > maxY) maxY = n->y;
    }

    // Garante que a matriz começa pelo menos em (1,1)
    if (minX > 1) minX = 1;
    if (minY > 1) minY = 1;

    // Calcula o tamanho da matriz
    *nRows = maxX - minX + 1;
    *nCols = maxY - minY + 1;

    if (*nRows <= 0 || *nCols <= 0) {
        printf("Dimensões inválidas: nRows=%d, nCols=%d\n", *nRows, *nCols);
        libertarNefastos(listaNefastos);
        return NULL;
    }

    // Aloca a matriz como vetor de ponteiros para linhas
    char** matriz = malloc(*nRows * sizeof(char*));
    if (!matriz) {
        perror("Erro na alocação da matriz");
        exit(1);
    }

    // Aloca cada linha e preenche com '.'
    for (int i = 0; i < *nRows; i++) {
        matriz[i] = malloc((*nCols + 1) * sizeof(char));
        if (!matriz[i]) {
            perror("Erro na alocação de uma linha da matriz");
            exit(1);
        }
        for (int j = 0; j < *nCols; j++) {
            matriz[i][j] = '.';
        }
        matriz[i][*nCols] = '\0'; // Torna cada linha uma string válida
    }

    // Coloca as antenas na matriz, ajustando índices pelo minX/minY
    for (const Antena* a = listaAntenas; a; a = a->next) {
        int linha = a->x - minX;
        int coluna = a->y - minY;
        if (linha >= 0 && linha < *nRows && coluna >= 0 && coluna < *nCols)
            matriz[linha][coluna] = a->freq;
        else
            printf("Antena fora dos limites: (%d, %d)\n", a->x, a->y);
    }

    // Coloca os nefastos na matriz, sem sobrepor antenas
    for (const Nefasto* n = listaNefastos; n; n = n->next) {
        int linha = n->x - minX;
        int coluna = n->y - minY;
        if (linha >= 0 && linha < *nRows && coluna >= 0 && coluna < *nCols) {
            if (matriz[linha][coluna] == '.')
                matriz[linha][coluna] = '#';
        }
        else {
            printf("Nefasto fora dos limites: (%d, %d)\n", n->x, n->y);
        }
    }

    // Liberta a lista de nefastos, já não é necessária
    libertarNefastos(listaNefastos);
    return matriz;
}

/// <summary>
/// Imprime a matriz no ecrã, linha por linha.
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
/// Liberta toda a memória alocada para a matriz, incluindo as linhas.
/// </summary>
/// <param name="matriz">Matriz a libertar.</param>
/// <param name="nRows">Número de linhas da matriz.</param>
void libertarMatriz(char** matriz, int nRows) {
    if (matriz == NULL) return;
    for (int i = 0; i < nRows; i++) {
        if (matriz[i] != NULL) {
            free(matriz[i]);
            matriz[i] = NULL;
        }
    }
    free(matriz);
    matriz = NULL;
}

#pragma endregion

#pragma region Funções de Carregamento de Ficheiros

/// <summary>
/// Carrega uma lista de antenas a partir de um ficheiro de texto, substituindo a lista atual.
/// Cada linha representa uma linha do "mapa" com antenas representadas por letras.
/// </summary>
/// <param name="filename">Nome do ficheiro a carregar.</param>
/// <param name="listaExistente">Lista de antenas atual (será libertada).</param>
/// <returns>Nova lista de antenas lida do ficheiro. Devolve NULL em caso de erro.</returns>
Antena* carregarAntenasDeFicheiro(const char* filename, Antena* listaExistente) {
    libertarAntenas(listaExistente); // Garante que a lista antiga é libertada primeiro

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Erro ao abrir ficheiro");
        return NULL;
    }

    Antena* novaLista = NULL;
    char linha[1024];
    int x = 1; 

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\r\n")] = '\0'; // Remove possíveis quebras de linha

        for (int y = 1; linha[y - 1] != '\0'; y++) {  // y começa em 1 para manter coerência com coordenadas
            if (linha[y - 1] != '.' && linha[y - 1] != ' ') {
                novaLista = inserirAntena(novaLista, linha[y - 1], x, y); // Insere antena encontrada
            }
        }
        x++;
    }

    fclose(fp);
    return novaLista;
}

#pragma endregion


