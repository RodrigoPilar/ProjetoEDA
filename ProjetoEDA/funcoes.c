/*
 *  @file funcoes.c
 *  @author Rodrigo Pilar
 *  @date 2025-03-29
 *  @project EDA
 *
 *  Implementa todas as fun��es para manipula��o das listas de antenas e nefastos,bem como fun��es auxiliares para cria��o, manipula��o da matriz e carregamento de uma matriz atrav�s de um ficheiro txt.
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "funcoes.h"

#pragma region Fun��es da Lista de Antenas

 /// <summary>
 /// Insere uma nova antena no in�cio da lista ligada.
 /// </summary>
 /// <param name="lista">Lista atual de antenas.</param>
 /// <param name="freq">Frequ�ncia da nova antena.</param>
 /// <param name="x">Coordenada X da antena.</param>
 /// <param name="y">Coordenada Y da antena.</param>
 /// <returns>Nova cabe�a da lista de antenas.</returns>
Antena* inserirAntena(Antena* lista, char freq, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (nova == NULL) {
        printf("Erro ao inserir nova antena.\n");
        return lista;
    }
    nova->freq = freq;
    nova->x = x;
    nova->y = y;
    nova->next = lista; // Aponta para o antigo in�cio da lista
    return nova;
}

/// <summary>
/// Remove uma antena da lista com base nas suas coordenadas.
/// </summary>
/// <param name="lista">Lista atual de antenas.</param>
/// <param name="x">Coordenada X da antena a remover.</param>
/// <param name="y">Coordenada Y da antena a remover.</param>
/// <returns>Nova cabe�a da lista ap�s remo��o.</returns>
Antena* removerAntena(Antena* lista, int x, int y) {
    Antena* ant = NULL;
    Antena* curr = lista;
    while (curr != NULL) {
        if (curr->x == x && curr->y == y) {
            if (ant == NULL)
                lista = curr->next; // A antena a remover � a primeira da lista
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
/// Imprime todas as antenas da lista no ecr� de forma tabular.
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
/// Liberta toda a mem�ria ocupada pela lista de antenas.
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

#pragma region Fun��es da Lista de Nefastos

/// <summary>
/// Insere um novo nefasto no in�cio da lista ligada.
/// </summary>
/// <param name="lista">Lista atual de nefastos.</param>
/// <param name="x">Coordenada X do nefasto.</param>
/// <param name="y">Coordenada Y do nefasto.</param>
/// <returns>Nova cabe�a da lista de nefastos.</returns>
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
/// Verifica se uma determinada posi��o nefasto j� existe na lista.
/// </summary>
/// <param name="lista">Lista atual de nefastos.</param>
/// <param name="x">Coordenada X.</param>
/// <param name="y">Coordenada Y.</param>
/// <returns>1 se existir, 0 caso contr�rio.</returns>
int existeNefasto(const Nefasto* lista, int x, int y) {
    while (lista != NULL) {
        if (lista->x == x && lista->y == y)
            return 1;
        lista = lista->next;
    }
    return 0;
}

/// <summary>
/// Calcula e cria a lista de posi��es nefastas a partir de pares de antenas com a mesma frequ�ncia.
/// </summary>
/// <param name="lista">Lista de antenas existentes.</param>
/// <returns>Lista de nefastos calculada com base nas simetrias.</returns>
Nefasto* calcularNefastos(const Antena* lista) {
    Nefasto* listaNefastos = NULL;
    for (const Antena* p = lista; p != NULL; p = p->next) {
        for (const Antena* q = p->next; q != NULL; q = q->next) {
            if (p->freq == q->freq) {
                // Calcula o ponto sim�trico de p em rela��o a q
                int x1 = 2 * q->x - p->x;
                int y1 = 2 * q->y - p->y;
                // Calcula o ponto sim�trico de q em rela��o a p
                int x2 = 2 * p->x - q->x;
                int y2 = 2 * p->y - q->y;
                // Apenas insere se n�o existir ainda na lista
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
/// Lista todos os nefastos presentes na lista ligada no ecr�.
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
/// Liberta da mem�ria todos os elementos da lista de nefastos.
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

#pragma region Fun��es da Matriz

/// <summary>
/// Cria uma matriz que representa graficamente a localiza��o das antenas e dos nefastos.
/// As antenas s�o representadas pela sua frequ�ncia (letra), os nefastos por '#' e os restantes espa�os por '.'.
/// </summary>
/// <param name="listaAntenas">Lista de antenas.</param>
/// <param name="nRows">Ponteiro onde ser� guardado o n�mero de linhas da matriz.</param>
/// <param name="nCols">Ponteiro onde ser� guardado o n�mero de colunas da matriz.</param>
/// <returns>Ponteiro para a matriz criada dinamicamente.</returns>
char** criarMatrizComNefastos(const Antena* listaAntenas, int* nRows, int* nCols) {
    if (!listaAntenas) {
        printf("Lista de antenas vazia. Sem dados para criar a matriz.\n");
        return NULL;
    }

    // Calcula os pontos nefastos a partir da lista de antenas fornecida
    Nefasto* listaNefastos = calcularNefastos(listaAntenas);

    // Determina os limites da matriz com base nas posi��es de antenas e nefastos
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;

    // Atualiza os limites m�nimos e m�ximos com base nas antenas
    for (const Antena* a = listaAntenas; a; a = a->next) {
        if (a->x < minX) minX = a->x;
        if (a->x > maxX) maxX = a->x;
        if (a->y < minY) minY = a->y;
        if (a->y > maxY) maxY = a->y;
    }

    // Atualiza tamb�m com base nos nefastos
    for (const Nefasto* n = listaNefastos; n; n = n->next) {
        if (n->x < minX) minX = n->x;
        if (n->x > maxX) maxX = n->x;
        if (n->y < minY) minY = n->y;
        if (n->y > maxY) maxY = n->y;
    }

    // Garante que a matriz come�a pelo menos em (1,1)
    if (minX > 1) minX = 1;
    if (minY > 1) minY = 1;

    // Calcula o tamanho da matriz
    *nRows = maxX - minX + 1;
    *nCols = maxY - minY + 1;

    if (*nRows <= 0 || *nCols <= 0) {
        printf("Dimens�es inv�lidas: nRows=%d, nCols=%d\n", *nRows, *nCols);
        libertarNefastos(listaNefastos);
        return NULL;
    }

    // Aloca a matriz como vetor de ponteiros para linhas
    char** matriz = malloc(*nRows * sizeof(char*));
    if (!matriz) {
        perror("Erro na aloca��o da matriz");
        exit(1);
    }

    // Aloca cada linha e preenche com '.'
    for (int i = 0; i < *nRows; i++) {
        matriz[i] = malloc((*nCols + 1) * sizeof(char));
        if (!matriz[i]) {
            perror("Erro na aloca��o de uma linha da matriz");
            exit(1);
        }
        for (int j = 0; j < *nCols; j++) {
            matriz[i][j] = '.';
        }
        matriz[i][*nCols] = '\0'; // Torna cada linha uma string v�lida
    }

    // Coloca as antenas na matriz, ajustando �ndices pelo minX/minY
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

    // Liberta a lista de nefastos, j� n�o � necess�ria
    libertarNefastos(listaNefastos);
    return matriz;
}

/// <summary>
/// Imprime a matriz no ecr�, linha por linha.
/// </summary>
/// <param name="matriz">Matriz a imprimir.</param>
/// <param name="nRows">N�mero de linhas da matriz.</param>
void imprimirMatriz(char** matriz, int nRows) {
    if (matriz == NULL || nRows <= 0) {
        printf("Matriz vazia ou dimens�es inv�lidas.\n");
        return;
    }
    for (int i = 0; i < nRows; i++) {
        if (matriz[i] != NULL)
            printf("%s\n", matriz[i]);
        else
            printf("(linha %d n�o alocada)\n", i);
    }
}

/// <summary>
/// Liberta toda a mem�ria alocada para a matriz, incluindo as linhas.
/// </summary>
/// <param name="matriz">Matriz a libertar.</param>
/// <param name="nRows">N�mero de linhas da matriz.</param>
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

#pragma region Fun��es de Carregamento de Ficheiros

/// <summary>
/// Carrega uma lista de antenas a partir de um ficheiro de texto, substituindo a lista atual.
/// Cada linha representa uma linha do "mapa" com antenas representadas por letras.
/// </summary>
/// <param name="filename">Nome do ficheiro a carregar.</param>
/// <param name="listaExistente">Lista de antenas atual (ser� libertada).</param>
/// <returns>Nova lista de antenas lida do ficheiro. Devolve NULL em caso de erro.</returns>
Antena* carregarAntenasDeFicheiro(const char* filename, Antena* listaExistente) {
    libertarAntenas(listaExistente); // Garante que a lista antiga � libertada primeiro

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Erro ao abrir ficheiro");
        return NULL;
    }

    Antena* novaLista = NULL;
    char linha[1024];
    int x = 1; 

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\r\n")] = '\0'; // Remove poss�veis quebras de linha

        for (int y = 1; linha[y - 1] != '\0'; y++) {  // y come�a em 1 para manter coer�ncia com coordenadas
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


