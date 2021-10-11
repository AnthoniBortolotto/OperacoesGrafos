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
    vector<int> dijkstra(int vOrigem, int vDestino);
    bool procurar(vector<int> visitados, int valor);
    vector<int> DjikstraTraduzido(vector<int> djikstra, int vOrigem, int vDestino);
    int obterDistDijkstra(vector<int> djikstra, int vOrigem, int vDestino);

    //uteis
    Aresta* buscarAresta(int vOrigem, int vDestino);
    Aresta* buscarArestaNOrientada(int vOrigem, int vDestino, vector<vector<Aresta*>> arestas);
    vector<Aresta *>  arestasVizinhas(int vertice);
    vector<int>  verticesVizinhos(int vertice);
    vector<int> vImpares();
    int somarDistDeArestas(vector<Aresta*> arestas);
    vector<vector<Aresta*>> removerDuplicatas(vector<vector<Aresta*>> conjunto);
    vector<Aresta*> tirarOrientacao(vector<Aresta*> arestas);
    void apagarAresNOrientada(Aresta* aresta);

    //Fleury
    bool eEuleriano();
    bool proximaArestaEValida(int vertice, Aresta* caminho);
    int numVAlcancaveis(int origem);
    void duplicarArestas(int origem);
    bool verificarVisita(vector<vector<int>> visitados, int v1, int v2);
    vector<vector<Aresta*>> combinarArestas(vector<Aresta*> conjunto, int tam);
    vector<int> fleury(int vOrigem);

    void hungaro(vector<vector<int>> matriz);
    void igualarLinhaColuna();
    int menorValorLinha(vector<vector<int>> matriz, int linha);
    int menorValorColuna(vector<vector<int>> matriz, int coluna);

    vector<vector<int>> igualarLinhaColuna(vector<vector<int>> matriz);

private:


    void vector<vector<int>>(vector<vector<int>> matriz);
};

