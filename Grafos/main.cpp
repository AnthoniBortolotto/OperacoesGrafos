
#include <iostream>
#include <vector>
#include "Aresta.h"
#include "Grafo.h"

using namespace std;

void exibirMatriz(vector<vector<int>> matriz) {
	for (int i = 0; i < matriz.size(); i++)
	{
		for (int j = 0; j < matriz[i].size(); j++)
		{
			cout << matriz[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{
    auto* a1 = new Aresta(5, 1, 2);
    auto* a2 = new Aresta(1, 4, 1);
    auto* a3 = new Aresta(3, 1, 4);

    auto* a4 = new Aresta(1, 4, 2);
    auto* a5 = new Aresta(1, 5, 2);
	auto* a6 = new Aresta(3, 2, 3);

	auto* a7 = new Aresta(5, 3, 5);

	auto* a8 = new Aresta(1, 4, 5);
	auto* a9 = new Aresta(1, 5, 4);

	auto* grafo = new Grafo();
	grafo = grafo->criarGrafo(5, 9, {a1, a2, a3, a4, a5, a6, a7, a8, a9});
   // criarGrafo(4,5, {a1,a2,a3,a4,a5});
	grafo->algoritmoFloyd();
	int input;
	bool continuar = true;
	while (continuar)
	{
		cout << "Menu\n 1- Problema do carteiro chines\n5-sair\n";
		cin >> input;
		switch (input)
		{
		case 1:
			cout << "matriz de custo" << endl;
			exibirMatriz(grafo->mCusto);
			cout << "\nmatriz de roteamento\n";
			exibirMatriz(grafo->mRoteamento);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			continuar = false;
			break;
		default:
			break;
		}
	}
	
    return 0;
}
