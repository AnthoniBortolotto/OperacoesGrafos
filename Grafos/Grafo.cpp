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
    this->numV = 0;
}

Grafo::~Grafo()
= default;

Grafo* Grafo::criarGrafo(int vertices, const vector<Aresta*>&novasArestas)
{
	auto* grafo = new Grafo();

	grafo->numV = vertices;

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
	microGrafo = microGrafo->criarGrafo(vertices.size(), arestasTraduzidas);
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

vector<int> Grafo::dijkstra(int vOrigem)
{
	int menor = -1;
	//Ant é a ordem em que os vértices são visitados
	vector<int> visitados(this->numV, 0), ordem(this->numV, -1), distancias(this->numV, -1);
	distancias[vOrigem] = 0; // a distância da origem até ela própria é 0
	ordem[vOrigem] = -2; //sinaliza a origem
	for (int cont = 0; cont < this->numV; cont++)
	{
		menor = this->menorDistancia(distancias, visitados); //começar teste com i = 1
		if (menor == -1) break; //melhorar mais tarde
		visitados[menor] = 1;
		auto aVizinhas = this->arestasVizinhas(menor);
		for (int j = 0; j < aVizinhas.size(); j++) // indice = 3 problema
		{
			int indice = aVizinhas[j]->destino; //chance de dar ruim alta aqui
			if (distancias[indice] == -1) //verifica se não existe ainda distância até o vizinho
			{
				if (distancias[menor] >= 0) distancias[indice] = distancias[menor] + aVizinhas[j]->peso;
				else distancias[indice] = aVizinhas[j]->peso;
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
	return ordem;
}

vector<int> Grafo::fleury(int vOrigem)
{
	int vAtual = vOrigem;
	vector<int> res;
	this->duplicarArestas(vOrigem);
	while (true)
	{
		auto aVizinhas = this->arestasVizinhas(vAtual);
		if (aVizinhas.empty())break;
		for (int i = 0; i < aVizinhas.size(); i++)
		{
			if (this->proximaArestaEValida(vAtual, aVizinhas[i])) {
				res.push_back(vAtual);
				vAtual = aVizinhas[i]->destino;
				//deletar aresta
				cout << "deletando aresta e percorrendo " << aVizinhas[i]->origem +1<< "-" << aVizinhas[i]->destino+1 << " ";
				this->apagarAresNOrientada(aVizinhas[i]);
				break;
			}
		}

	}
	if (res.empty()) res.push_back(vOrigem);
	cout << "caminho completo:" << endl;
	for (auto ar : res) cout << ar+1 << "-"; //pra ficar igual o grafo
	cout << vOrigem+1 << endl;
	return res;
}

int Grafo::menorDistancia(vector<int> dist, vector<int> visitados)
{
	int indiceDistMenor = -1;
	for (int i = 0; i < this->numV; ++i) {
		if (visitados[i] == 0 && dist[i] >= 0 && (indiceDistMenor == -1 || (dist[i] < dist[indiceDistMenor]))) {
			indiceDistMenor = i;
		}
	}
	return  indiceDistMenor;
}


//retorna um array com a ordem dos vertices
vector<int> Grafo::DjikstraTraduzido(vector<int> djikstra, int vOrigem, int vDestino)
{
	vector<int> ordem;
	if (vOrigem == vDestino) {
		ordem.push_back(vOrigem);
		return ordem;
	}
	int i = vDestino;
	while (true) { // problema um diz que o melhor caminho é o outro, causando loop infinito
		ordem.push_back(djikstra[i]);
		i = ordem[ordem.size() - 1];
		if (i == vOrigem) break; //trocar depois
	}
	vector<int> inverso;
	for (i = ordem.size() - 1; i >= 0; i--)
	{
		inverso.push_back(ordem[i]);
	}
	inverso.push_back(vDestino);
	return inverso;
}
//através do resultado do djikstra, da origem e destino retorna a distancia
int Grafo::obterDistDijkstra(vector<int> djikstra, int vOrigem, int vDestino) // testado
{
	auto traducao = this->DjikstraTraduzido(djikstra, vOrigem, vDestino);
	int distancia = 0;
	if (traducao.size() == 1) return distancia;

	for (int i = 1; i < traducao.size(); i++)
	{
		distancia += this->buscarAresta(traducao[i - 1], traducao[i])->peso;
	}
	return distancia;
}

Aresta* Grafo::buscarAresta(int vOrigem, int vDestino)
{
	for (auto aresta : this->arestas) {
		if (aresta->origem == vOrigem && aresta->destino == vDestino) return aresta;
	}
	return NULL;
}


vector<Aresta*> Grafo::arestasVizinhas(int vertice) {
	vector<Aresta*> vizinhos;
	for (int i = 0; i < this->arestas.size(); i++) {
		if (this->arestas[i]->origem == vertice)
			vizinhos.push_back(this->arestas[i]);
	}
	return vizinhos;
}

//retorna os vértices impares
vector<int> Grafo::vImpares() // testado
{
	vector<int> vI;
	for (auto vertice : this->vertices)
	{
		if (this->arestasVizinhas(vertice).size() % 2 != 0) vI.push_back(vertice);
	}
	return vI;
}

void Grafo::apagarAresNOrientada(Aresta * aresta)
{
	Aresta* apagar;
	for (auto are : this->arestas) {
		if (are->peso == aresta->peso && are->destino == aresta->origem && are->origem == aresta->destino) {
			apagar = are;
			break;
		}
	}
	this->arestas.erase(std::remove(this->arestas.begin(), this->arestas.end(), apagar), this->arestas.end());
	this->arestas.erase(std::remove(this->arestas.begin(), this->arestas.end(), aresta), this->arestas.end());
}

bool Grafo::proximaArestaEValida(int vertice, Aresta * caminho)
{
	cout << "checando se caminho " << (caminho->origem) + 1 << "-" << (caminho->destino) + 1 << " eh valido" << endl;
	auto arestasVizinhas = this->arestasVizinhas(vertice);
	//se há apenas uma direção então ela é válida
	if (arestasVizinhas.size() == 1) return true;
	//checar se é ponte
	//auto numVAlcancaveis = this->verticesVizinhos(vertice); //ver se não é djikstra
	auto numvAlcancaveisAntes = this->numVAlcancaveis(vertice);
	//remover a aresta caminho das arestas
	//remove qualquer aresta igual a caminho 
	this->apagarAresNOrientada(caminho); //funciona
	auto numvAlcancaveisDepois = this->numVAlcancaveis(vertice);
	this->arestas.push_back(caminho);
	this->arestas.push_back(new Aresta(caminho->peso, caminho->destino, caminho->origem));
	if (numvAlcancaveisAntes > numvAlcancaveisDepois) {
		cout << "nao eh valido" << endl;
		return false;
	}
	cout << "eh valido" << endl;
	return true;
}

int Grafo::numVAlcancaveis(int origem)
{
	//jeito com floyd
	int cont = 0;
	this->algoritmoFloyd();
	for (int i = 0; i < this->mCusto[origem].size(); i++)
	{
		if (this->mCusto[origem][i] != -1) cont++;
	}
	return cont;
}

bool checarMarcados(vector<int> marcados) {
	for (auto marca : marcados) if (marca == 0) return false;
	return true;
}

//cria as novas arestas em grafos não eulerianos
void Grafo::duplicarArestas(int origem) //apenas não direcionado
{
	auto vImpares = this->vImpares();
	if (vImpares.size() == 0) return;
	cout << "duplicando arestas" << endl;
	vector<vector<int>> visitado; //recebe os pares de vértices que foram visitados
	vector<Aresta*> novasArestas;
	int dist = 0;
	//gera arestas entre cada vertice impar
	cout << "gerando arestas entre cada vertice impar" << endl;
	for (auto vImpar1 : vImpares) {
		for (auto vImpar2 : vImpares) {
			if (vImpar1 != vImpar2 && !verificarVisita(visitado, vImpar1, vImpar2)) { //impede repetição de aresta por não ser orientado
				dist = this->obterDistDijkstra(this->dijkstra(vImpar1), vImpar1, vImpar2);
				//inseria aresta não direcionada
				novasArestas.push_back(new Aresta(dist, vImpar1, vImpar2));
				novasArestas.push_back(new Aresta(dist, vImpar2, vImpar1));
				visitado.push_back({ vImpar1, vImpar2 });
				cout << "gerando aresta " << vImpar1+1 << "-" << vImpar2+1 << " peso: " << dist << endl;
			}
		}
	}
	int tamConjunto = vImpares.size() / 2; //pra definir se vão ser feitas duplas, trios, etc... //funciona

	auto microGrafo = this->criarMicroGrafo(vImpares, novasArestas);
	int menor = -1;
	int melhori = -1;
	int melhorj = -1;
	vector<int> marcados(microGrafo->numV, 0);
	vector<int> bons;
	while (!checarMarcados(marcados)) {
		for (int i = 0; i < microGrafo->numV; i++)
		{
			if (marcados[i] == 0)
			{
				int dist = 0;
				for (int j = 0; j < microGrafo->numV; j++)
				{
					if (marcados[j] == 0 && i != j) {
						dist = microGrafo->obterDistDijkstra(microGrafo->dijkstra(i), i, j);
						if (menor == -1 || menor > dist)
						{
							menor = dist;
							melhori = i;
							melhorj = j;
						}
					}
				}
				marcados[melhori] = 1;
				marcados[melhorj] = 1;
				bons.push_back(melhori);
				bons.push_back(melhorj);
				menor = -1;
			}
			
		}
	}
	//só traduzir de volta
	vector<Aresta*> arestasCertas;
	for (int i = 0; i < bons.size() - 1; i = i + 2)
	{
		auto arestaAtual = microGrafo->buscarAresta(bons[i], bons[i+1]);
		arestaAtual->origem = vImpares[arestaAtual->origem];
		arestaAtual->destino = vImpares[arestaAtual->destino];
		arestasCertas.push_back(arestaAtual);
		arestasCertas.push_back(new Aresta(arestaAtual->peso, arestaAtual->destino, arestaAtual->origem)); // por que é não orientado
		cout << "menor aresta selecionada e criada " << (arestaAtual->origem) + 1 << "-" << (arestaAtual->destino) + 1 << " com peso: " << arestaAtual->peso << endl;
	}

	this->arestas.insert(this->arestas.end(), arestasCertas.begin(), arestasCertas.end());
}

bool Grafo::verificarVisita(vector<vector<int>> visitados, int v1, int v2)
{
	if (visitados.empty()) return false;
	vector<int> dupla1 = { v1, v2 };
	vector<int> dupla2 = { v2, v1 };
	for (auto visitado : visitados) {
		if (dupla1 == visitado || dupla2 == visitado) return true;
	}
	return false;
}