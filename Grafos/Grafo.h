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

    bool verificarMatriz(int alvo, vector<vector<int>> matriz);


    //Dijsktra
    int menorDistancia(vector<int> dist, vector<int> visitados);
    vector<int> dijkstra(int vOrigem, int vDestino, int &distTotal);
    vector<int> fleury(int vOrigem);
    bool procurar(vector<int> visitados, int valor);
    vector<int> DjikstraTraduzido(vector<int> djikstra, int vOrigem, int vDestino);
    //uteis
    vector<Aresta *>  arestasVizinhas(int vertice);
    vector<int>  verticesVizinhos(int vertice);
    vector<int> vImpares();
    //Fleury
    bool eEuleriano();
    bool proximaArestaEValida(int vertice, Aresta* caminho);
    int numVAlcancaveis(int origem);
private:


};

