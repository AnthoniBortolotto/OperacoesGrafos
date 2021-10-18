#pragma once

#include <vector>
#include "Aresta.h"
#include "string"

class Grafo
{
public:

    vector<int> fleury(int vOrigem);
    static Grafo *criarGrafo(int vertices, const vector<Aresta *> &novasArestas);

private:
    vector<Aresta *> arestas;
    int numV;
    vector<vector<int>> mCusto;
    vector<int> vertices;

    Grafo();
    ~Grafo();

    void algoritmoFloyd();
    vector<vector<int>> matrizCusto();
    vector<vector<int>> matrizRoteamento();
    Aresta *retornarArestaAdjacente(int vOrigem, int vDestino);
    Grafo* criarMicroGrafo(vector<int> vertices, vector<Aresta*> arestas);
    bool verificarMatriz(int alvo, vector<vector<int>> matriz);


    //Dijsktra
    int menorDistancia(vector<int> dist, vector<int> visitados);
    vector<int> dijkstra(int vOrigem, int vDestino);

    vector<int> DjikstraTraduzido(vector<int> djikstra, int vOrigem, int vDestino);
    int obterDistDijkstra(vector<int> djikstra, int vOrigem, int vDestino);

    //uteis
    Aresta* buscarAresta(int vOrigem, int vDestino);

    vector<Aresta *>  arestasVizinhas(int vertice);

    vector<int> vImpares();

    void apagarAresNOrientada(Aresta* aresta);

    bool proximaArestaEValida(int vertice, Aresta* caminho);
    int numVAlcancaveis(int origem);
    void duplicarArestas(int origem);
    bool verificarVisita(vector<vector<int>> visitados, int v1, int v2);

};

