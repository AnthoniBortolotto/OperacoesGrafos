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

	for (int i = 0; i < grafo->numV; i++)
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
				auto aAdjascente = retornarArestaAdjacente(i + 1, j + 1); //Passa a Vértice de Origem e Vertice Destino para verificar se é adjacente.
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
				matriz[i][j] = i + 1;
			else
			{
				auto aAdjascente = retornarArestaAdjacente(i + 1, j + 1);
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

vector<int> Grafo::dijkstra(int vOrigem, int vDestino)
{
	int menor = -1;
	//Ant é a ordem em que os vértices são visitados
	vector<int> visitados(this->numV, 0), ordem(this->numV, -1), distancias(this->numV, -1);
	distancias[vOrigem] = 0;
	ordem[vOrigem] = vOrigem;// a distância da origem até ela própria é 0
	for (int cont = 0; cont < this->numV; cont++)
	{
		menor = this->menorDistancia(distancias, visitados); //começar teste com i = 1
		if (menor == -1) break; //melhorar mais tarde
		visitados[menor] = 1;
		auto aVizinhas = this->arestasVizinhas(menor);
		for (int j = 0; j < aVizinhas.size(); j++)
		{
			//descobrir qual dado das arestas vizinhas se quer
			int indice = aVizinhas[j]->destino; //chance de dar ruim alta aqui
			if (distancias[indice] == -1) //verifica se não existe distância até o vizinho
			{
				distancias[indice] = distancias[menor] + aVizinhas[j]->peso;
				ordem[indice] = menor;
			}
			else
			{
				if (distancias[indice] > (distancias[menor] + aVizinhas[j]->peso))
				{
					distancias[indice] = distancias[menor] + aVizinhas[j]->peso;
					ordem[indice] = menor;
				}
			}
		}
	}
	//exibir matriz
	cout << "vetor de distancias\n";
	for (int i = 0; i < distancias.size(); i++)
	{
		cout << distancias[i] << " ";

	}
	cout << "\nordem de percorrer\n";
	for (int i = 0; i < ordem.size(); i++)
	{
		cout << ordem[i] << " ";

	}
	return ordem;
}

int Grafo::menorDistancia(vector<int> dist, vector<int> visitados)
{
	int indiceDistMenor = -1;
	for (int i = 0; i < this->numV; ++i) {
		if (visitados[i] == 0 && (indiceDistMenor == -1 || (dist[i] < dist[indiceDistMenor] && dist[i] >= 0))) {
			indiceDistMenor = i;
		}
	}
	return  indiceDistMenor;
}



bool Grafo::procurar(vector<int> visitados, int valor) {

	for (int i = 0; i < visitados.size(); i++)
	{
		if (visitados[i] == valor) return true;
	}
	return false;
}

vector<Aresta*> Grafo::arestasVizinhas(int vertice) {
	vector<Aresta*> vizinhos;
	for (int i = 0; i < this->numA; i++) {
		if (this->arestas[i]->origem == vertice)
			vizinhos.push_back(this->arestas[i]);
	}
	return vizinhos;
}
