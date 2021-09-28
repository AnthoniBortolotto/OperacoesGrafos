#include "Grafo.h"
#include "Aresta.h"

Grafo::Grafo()
{
    this->numA = 0;
    this->numV = 0;
}

Grafo::~Grafo()
= default;

Grafo* Grafo::criarGrafo(int vertices, int arestas, const vector<Aresta *>& novasArestas)
{
    auto* grafo = new Grafo();

    grafo->numV = vertices;
    grafo->numA = arestas;

    grafo->arestas = novasArestas;

    return grafo;
}

vector<vector<int>> Grafo::algoritmoFloyd()
{
    //return matrizCusto();
}

vector<vector<int>> Grafo::matrizCusto()
{
    vector<vector<int>> matriz = {};
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            if(i == j)
                matriz[i][j] = 0;
            else
            {
                matriz[i][j] = retornarArestaAdjacente(arestas[i]->origem, arestas[j]->destino)->peso;
                cout << arestas[i]->origem;
            }
        }
    }
}

Aresta *Grafo::retornarArestaAdjacente(string vOrigem, string vDestino) {
    Aresta* aCerta = nullptr;
    for (int i = 0; i < this->arestas.size(); i++) {
        if(this->arestas[i]->origem == vOrigem && this->arestas[i]->destino == vDestino)
            aCerta = this->arestas[i];
    }
    return aCerta;
}


