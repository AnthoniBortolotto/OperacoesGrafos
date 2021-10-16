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
			cout << tempMRoteamento[i][j] << " ";
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
				this->arestas.erase(std::remove(this->arestas.begin(), this->arestas.end(), aVizinhas[i]), this->arestas.end());
				break;
			}
		}

	}
	if (res.empty()) res.push_back(vOrigem);
	return res;
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

vector<int> Grafo::verticesVizinhos(int vertice)
{
	auto aVizinhas = this->arestasVizinhas(vertice);
	vector<int> vVizinhos;
	bool adicionar;
	for (int i = 0; i < aVizinhas.size(); i++)
	{
		adicionar = true;
		for (int j = 0; j < vVizinhos.size(); j++)
		{
			if (vVizinhos[j] == aVizinhas[i]->destino) adicionar = false;
		}
		if (adicionar) vVizinhos.push_back(aVizinhas[i]->destino);
	}
	return vVizinhos;
}

vector<int> Grafo::vImpares()
{
	vector<int> vI;
	for (auto vertice : this->vertices)
	{
		if ((this->arestasVizinhas(vertice).size() / 2) % 2 != 0) vI.push_back(vertice);
	}
	return vI;
}

bool Grafo::eEuleriano()
{
	int numVerticesImpares = 0;
	int numArestas;
	for (int i = 0; i < this->numV; i++) {
		numArestas = this->arestasVizinhas(i).size();
		if (numArestas % 2 != 0) numVerticesImpares++;
	}
	if (numVerticesImpares == 0 || numVerticesImpares == 2) return true;
	return false;
}

bool Grafo::proximaArestaEValida(int vertice, Aresta * caminho)
{
	auto arestasVizinhas = this->arestasVizinhas(vertice);
	//se há apenas uma direção então ela é válida
	if (arestasVizinhas.size() == 1) return true;
	//checar se é ponte
	//auto numVAlcancaveis = this->verticesVizinhos(vertice); //ver se não é djikstra
	auto numvAlcancaveisAntes = this->numVAlcancaveis(vertice);
	//remover a aresta caminho das arestas
	//remove qualquer aresta igual a caminho 
	this->arestas.erase(std::remove(this->arestas.begin(), this->arestas.end(), caminho), this->arestas.end()); //funciona
	auto numvAlcancaveisDepois = this->numVAlcancaveis(vertice);
	this->arestas.push_back(caminho);
	if (numvAlcancaveisAntes > numvAlcancaveisDepois) return false;
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

Grafo* Grafo::duplicarArestas(int origem)
{
	return nullptr;
}
