#pragma once

#include <vector>
#include "Aresta.h"
#include "string"

class Grafo
{
public:

    vector<Aresta *> arestas;
    int numV;
    int numA;
    vector<vector<int>> mCusto;
    vector<vector<int>> mRoteamento;
    vector<int> vertices;

    Grafo();
    ~Grafo();

    static Grafo *criarGrafo(int vertices, int arestas, const vector<Aresta *> &novasArestas);
    void algoritmoFloyd();
    vector<vector<int>> matrizCusto();
    vector<vector<int>> matrizRoteamento();
    Aresta *retornarArestaAdjacente(int vOrigem, int vDestino);
    Grafo* criarMicroGrafo(vector<int> vertices, vector<Aresta*> arestas);
    bool verificarMatriz(int alvo, vector<vector<int>> matriz);

private:


};

