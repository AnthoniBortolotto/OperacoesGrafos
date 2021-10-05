#include "Grafo.h"
#include "Aresta.h"
#include <list>
#include <queue>
#include <algorithm>

using namespace std;
Grafo::Grafo()
{
    this->numA = 0;
    this->numV = 0;
}

Grafo::~Grafo()
= default;

Grafo* Grafo::criarGrafo(int vertices, int arestas, const vector<Aresta*>&novasArestas)
{
    auto* grafo = new Grafo();

    grafo->numV = vertices;
    grafo->numA = arestas;

    grafo->arestas = novasArestas;

    for (int i = 0; i< grafo->numV; i++)
    {
        grafo->vertices.push_back(i);
    }
    return grafo;
}

void Grafo::algoritmoFloyd()
{
    auto tempMCusto = this->matrizCusto();
    auto tempMRoteamento = this->matrizRoteamento();

    int k = 0;
    while (this->verificarMatriz(-1, tempMCusto) && k < tempMCusto.size()) {
        cout << "matriz de custo: " << k << endl;
        for (int i = 0; i < tempMCusto.size(); i++)
        {
            for (int j = 0; j < tempMCusto[i].size(); j++)
            {
                cout << tempMCusto[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\nmatriz de roteamento: " << k << "\n";
        for (int i = 0; i < tempMRoteamento.size(); i++)
        {
            for (int j = 0; j < tempMRoteamento[i].size(); j++)
            {
                cout << tempMRoteamento[i][j] << " ";
            }
            cout << "\n";
        }
        //EXIBIÇÃO DE DADOS

        for (int i = 0; i < tempMCusto.size(); i++)
        {
            for (int j = 0; j < tempMCusto[i].size(); j++)
            {
                if ((tempMCusto[i][k] != -1 && tempMCusto[k][j] != -1) && (((tempMCusto[i][k] + tempMCusto[k][j]) < tempMCusto[i][j]) || tempMCusto[i][j] == -1)) {
                    tempMCusto[i][j] = tempMCusto[i][k] + tempMCusto[k][j];
                    tempMRoteamento[i][j] = tempMRoteamento[i][k];
                }
            }
        }

        k++;
    }
    this->mCusto = tempMCusto;
    this->mRoteamento = tempMRoteamento;
}

vector<vector<int>> Grafo::matrizCusto()
{
    vector<int> colunas(this->numV, -1);
    vector<vector<int>> matriz(this->numV, colunas);
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            if (i == j)
                matriz[i][j] = 0;
            else
            {
                auto aAdjascente = retornarArestaAdjacente(i+1, j+1); //Passa a Vértice de Origem e Vertice Destino para verificar se é adjacente.
                if (aAdjascente != NULL)  //Se não for adjacente, o valor atual na matriz fica -1, caso contrario, pega o peso.
                    matriz[i][j] = aAdjascente->peso;
                else
                    matriz[i][j] = -1;
            }
        }
    }
    return matriz;
}

vector<vector<int>> Grafo::matrizRoteamento()
{
    vector<int> colunas(this->numV, 0);
    vector<vector<int>> matriz(this->numV, colunas);
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            if (i == j)
                matriz[i][j] = i+1;
            else
            {
                auto aAdjascente = retornarArestaAdjacente(i+1, j+1);
                if (aAdjascente != NULL) matriz[i][j] = aAdjascente->destino;
                else matriz[i][j] = 0;
            }
        }
    }
    return matriz;
}

Aresta* Grafo::retornarArestaAdjacente(int vOrigem, int vDestino) {
    for (int i = 0; i < this->arestas.size(); i++) {
        if (this->arestas[i]->origem == vOrigem && this->arestas[i]->destino == vDestino)
            return this->arestas[i];
    }
    return NULL;
}

bool Grafo::verificarMatriz(int alvo, vector<vector<int>> matriz) {
    for (int i = 0; i < matriz.size(); i++)
    {
        for (int j = 0; j < matriz[i].size(); j++)
        {
            if (matriz[i][j] == alvo) return true;
        }
    }
    return false;
}

int Grafo::dijkstra(int vOrigem, int vDestino) {
//    int
//    vector<int> dist(this->numV, -1); // Cria vetor de distancias com todo valor como -1
//    dist[vOrigem] = 0; // seta a distancia da origem para 0
    vector<int> visitados; // cria um vetor para guardar os vertices visitados
    int indiceMenorDist = -1;
    if(vOrigem == vDestino) return  0;

//    for (int k = 0; k < this->numV; k++) { //Iterando todos os vertices
//        indiceMenorDist = menorDistancia(dist, visitados); //pega o indice com a menor distancia
//        for(int i = 0; i < this->numV; i++)
//        {
//            for(int j = 0; j < this->numA; j++){
//                if(this->arestas[0]->peso == dist[indiceMenorDist]
//                && this->arestas[1]->peso == dist[i])
//                {
//                    if(this->arestas[2]->peso != -1 and !this->procurar(visitados, i) and dist[i] > dist[indiceMenorDist]+arestas[2]->peso)
//                    {
//                        dist[i] = dist[indiceMenorDist]+arestas[2]->peso;
//                    }
//                }
//            }
//        }
//        visitados.push_back(indiceMenorDist);
//    }
    return dist[vDestino];
}

int Grafo::menorDistancia(vector<int> dist, vector<int> visitados)
{
    int distanciaMin = -1;
    int indice = -1;
    for (int i = 0; i < this->numV; ++i) {
        if(distanciaMin == -1 || (dist[i] < distanciaMin && this->procurar(visitados, this->vertices[i]))){
            distanciaMin = dist[i];
            indice = i;
        }
    }
    return  indice;
}



bool Grafo::procurar(vector<int> visitados, int valor) {

    auto retorno = std::find(begin(visitados), end(visitados), valor);
    return retorno != std::end(visitados);
}

vector<Aresta *> Grafo::arestasVizinhas(int vertice) {
    vector<Aresta *> vizinhos;
    for(int i = 0; i < this->numA; i++){
        if(this->arestas[i]->origem == vertice)
            vizinhos.push_back(this->arestas[i]);
    }
    return vizinhos;
}
