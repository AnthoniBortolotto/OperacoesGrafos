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
    vector<string> vertices;

    Grafo();
    ~Grafo();

    static Grafo *criarGrafo(int vertices, int arestas, const vector<Aresta *> &novasArestas);
    vector<vector<int>> algoritmoFloyd();
    vector<vector<int>> matrizCusto();
    Aresta *retornarArestaAdjacente(string vOrigem, string vDestino);

private:


};

