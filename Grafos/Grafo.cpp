#include "Grafo.h"
#include "Aresta.h"
#include <list>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

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
	//  Exibir dados
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
	//precisa 2 vezes
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
			cout << tempMRoteamento[i][j] + 1 << " ";
		}
		cout << "\n";
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
				auto aAdjascente = retornarArestaAdjacente(i, j); //Passa a Vértice de Origem e Vertice Destino para verificar se é adjacente.
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
				matriz[i][j] = i;
			else
			{
				auto aAdjascente = retornarArestaAdjacente(i, j);
				if (aAdjascente != NULL) matriz[i][j] = aAdjascente->destino;
				else matriz[i][j] = -1;
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

Grafo* Grafo::criarMicroGrafo(vector<int> vertices, vector<Aresta*> arestas)
{
	vector<Aresta*> arestasTraduzidas;
	for (auto aresta : arestas) {
		int src = -1;
		int dest = -1;
		for (int i = 0; i < vertices.size(); i++) {
			if (aresta->destino == vertices[i]) {
				dest = i;
				break;
			}
		}
		for (int i = 0; i < vertices.size(); i++) {
			if (aresta->origem == vertices[i]) {
				src = i;
				break;
			}
		}
		arestasTraduzidas.push_back(new Aresta(aresta->peso, src, dest));
	}
	auto microGrafo = new Grafo();
	microGrafo = microGrafo->criarGrafo(vertices.size(), arestasTraduzidas.size(), arestasTraduzidas);
	return microGrafo;
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


bool checarMarcados(vector<int> marcados) {
	for (auto marca : marcados) if (marca == 0) return false;
	return true;
}