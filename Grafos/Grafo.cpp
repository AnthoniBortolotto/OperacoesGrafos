#include "Grafo.h"
#include "Aresta.h"

Grafo::Grafo()
{
    this->numA = 0;
    this->numV = 0;
}

Grafo::~Grafo()
{
}

Grafo* Grafo::criarGrafo(int vertices, int arestas, vector<Aresta> novasArestas)
{
    Grafo* grafo = new Grafo();

    grafo->numV = vertices;
    grafo->numA = arestas;

    grafo->arestas = novasArestas;

    return grafo;
}

vector<vector<int>> Grafo::algoritmoFloyd()
{
    return vector<vector<int>>();
}

vector<vector<int>> Grafo::matrizCusto()
{
    return vector<vector<int>>();
}


