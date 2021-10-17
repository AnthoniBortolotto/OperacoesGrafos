
#include <iostream>
#include <vector>
#include "Aresta.h"
#include "Grafo.h"

using namespace std;

int main()
{

	//questão 3
	int input  = 0;
	bool continuar = true;

	//Atividade Carteiro Chines
	//vertice 1
	auto* a1 = new Aresta(2, 0, 1);
	auto* a2 = new Aresta(2, 1, 0);

	auto* a3 = new Aresta(2, 0, 4);
	auto* a4 = new Aresta(2, 4, 0);

	//vertice 2
	auto* a5 = new Aresta(1, 1, 4);
	auto* a6 = new Aresta(1, 4, 1);

	auto* a7 = new Aresta(1, 1, 3);
	auto* a8 = new Aresta(1, 3, 1);

	auto* a9 = new Aresta(3, 1, 2);
	auto* a10 = new Aresta(3, 2, 1);

	//vertice 3
	auto* a11 = new Aresta(1, 2, 3);
	auto* a12 = new Aresta(1, 3, 2);

	auto* a13 = new Aresta(6, 2, 6);
	auto* a14 = new Aresta(6, 6, 2);

	//vertice 4
	auto* a15 = new Aresta(5, 3, 4);
	auto* a16 = new Aresta(5, 4, 3);

	auto* a17 = new Aresta(3, 3, 5);
	auto* a30 = new Aresta(3, 5, 3);

	auto* a18 = new Aresta(3, 3, 8);
	auto* a19 = new Aresta(3, 8, 3);

	auto* a20 = new Aresta(2, 3, 7);
	auto* a21 = new Aresta(2, 7, 3);

	//vertice 6

	auto* a22 = new Aresta(2, 5, 6);
	auto* a23 = new Aresta(2, 6, 5);

	auto* a24 = new Aresta(5, 5, 8);
	auto* a25 = new Aresta(5, 8, 5);

	//vertice 7
	auto* a26 = new Aresta(2, 6, 7);
	auto* a27 = new Aresta(2, 7, 6);

	//vetice 8
	auto* a28 = new Aresta(1, 7, 8);
	auto* a29 = new Aresta(1, 8, 7);

	Grafo* grafo;
	int numV = 9;
	int numA = 30;
	grafo = Grafo::criarGrafo(numV, numA, { a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30});
	vector<int> res;

	while (continuar)
	{
		cout << "Menu - Problema do Carteiro Chines\n";
		cout << "\n1 - Fleury\n";
		cout << "2 - Sair\n";
		cin >> input;
		switch (input)
		{
		case 1:
			grafo->fleury(0);
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