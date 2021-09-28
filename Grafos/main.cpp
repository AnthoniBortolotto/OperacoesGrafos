
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
    auto* a1 = new Aresta(1, 1, 2);
    auto* a2 = new Aresta(4, 2, 3);
    auto* a3 = new Aresta(2, 2, 3);
    auto* a4 = new Aresta(2, 1, 3);
    auto* a5 = new Aresta(1, 3, 4);

	auto* grafo = new Grafo();
	grafo = grafo->criarGrafo(4, 5, {a1, a2, a3, a4, a5});
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
