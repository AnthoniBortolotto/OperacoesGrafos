#include "Grafo.h"
#include "Aresta.h"

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

	return grafo;
}

void Grafo::algoritmoFloyd()
{
	auto tempMCusto = this->matrizCusto();
	cout << "matriz de custo" << endl;
	for (int i = 0; i < tempMCusto.size(); i++)
	{
		for (int j = 0; j < tempMCusto[i].size(); j++)
		{
			cout << tempMCusto[i][j] << " ";
		}
		cout << "\n";
	}
	auto tempMRoteamento = this->matrizRoteamento();
	cout << "\nmatriz de roteamento\n";
	for (int i = 0; i < tempMRoteamento.size(); i++)
	{
		for (int j = 0; j < tempMRoteamento[i].size(); j++)
		{
			cout << tempMRoteamento[i][j] << " ";
		}
		cout << "\n";
	}

	int k = 0;
	//  vector<vector<vector<int>>> matrizes;
	 // matrizes.push_back(mCusto);
	while (this->verificarMatriz(NULL, tempMCusto) && k < tempMCusto.size()) {
		for (int i = 0; i < tempMCusto.size(); i++)
		{
			for (int j = 0; j < tempMCusto[i].size(); j++)
			{
				if (tempMCusto[i][k] != NULL && tempMCusto[k][j] != NULL && (tempMCusto[i][k] + tempMCusto[k][j]) < tempMCusto[i][j]) {
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
	vector<int> colunas(this->numV, 0);
	vector<vector<int>> matriz(this->numV, colunas);
	for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz[i].size(); j++) {
			if (i == j)
				matriz[i][j] = 0;
			else
			{
				auto aAdjascente = retornarArestaAdjacente(i, j);
				if (aAdjascente != NULL) matriz[i][j] = aAdjascente->peso;
				else matriz[i][j] = NULL;
				//cout << arestas[i]->origem;
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
	Aresta* aCerta = NULL;
	for (int i = 0; i < this->arestas.size(); i++) {
		if (this->arestas[i]->origem == vOrigem && this->arestas[i]->destino == vDestino)
			aCerta = this->arestas[i];
	}
	return aCerta;
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