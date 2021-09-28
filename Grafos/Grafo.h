#pragma once

#include <vector>
#include "Aresta.h"

class Grafo
{
public:

    vector<Aresta> arestas;
    int numV;
    int numA;
    vector<string> vertices;

    Grafo();
    ~Grafo();

    Grafo* criarGrafo(int vertices, int arestas, vector<Aresta> novasArestas);

    vector<vector<int>> algoritmoFloyd();

    vector<vector<int>> matrizCusto();

private:

};

