
#include <iostream>
#include <vector>
#include "Hungaro.h"
#include "Aresta.h"
#include "Grafo.h"

using namespace std;


void lerFloyd(Grafo* grafo, int origem, int destino) {
	int dist = grafo->mCusto[origem][destino];
	int i = origem;
	cout << "a rota de custo minimo entre o vertice " << origem + 1 << " e o vertice " << destino + 1 << " e:\n";
	while (i != destino)
	{
		cout << i + 1 << "-";
		i = grafo->mRoteamento[i][destino];
	}
	cout << i + 1;
	cout << "\nseu custo e: " << dist << endl;
}

int main()
{

	//vertice 1
	auto* a1 = new Aresta(2, 0, 1);
	auto* a2 = new Aresta(4, 0, 2);
	//vertice 2
	auto* a3 = new Aresta(1, 1, 0);
	auto* a4 = new Aresta(1, 1, 2);

	//vertice 3
	auto* a5 = new Aresta(5, 2, 3);
	//vertice 4
	auto* a6 = new Aresta(8, 3, 2);
	auto* a7 = new Aresta(3, 3, 0);
	auto* a8 = new Aresta(4, 3, 1);

	int input  = 0;
	bool continuar = true;
	int origem = 0;
	int destino = 2;

	Grafo* grafo;
	int numV = 4;
	int numA = 8;
	grafo = Grafo::criarGrafo(numV, numA, { a1, a2, a3, a4, a5, a6, a7, a8});
	vector<int> res;

	while (continuar)
	{
		cout << "Menu - Questao 1\n";
		cout << "1 - Floyd\n";
		cout << "2 - Sair\n";
		cin >> input;
		switch (input)
		{
		case 1:
            grafo->algoritmoFloyd();
			lerFloyd(grafo, 0, 3);
			lerFloyd(grafo, 2, 1);
			break;
		case 2:
			continuar = false;
			break;
		default:
			break;
		}
	}
	
    return 0;
}