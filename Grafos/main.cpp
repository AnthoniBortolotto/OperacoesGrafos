
#include <iostream>
#include <vector>
#include "Aresta.h"
#include "Grafo.h"

using namespace std;

void exibirMatriz(const vector<vector<int>>& matriz) {
	for (auto & i : matriz) //pq Mattes? Quem entende essa porra?
	{
		for (int j : i)
		{
			cout << j << " ";
		}
		cout << "\n";
	}
}

void exibirDijkstra(vector<int> djikstra, int vOrigem, int vDestino, int DistTotal) {
	vector<int> ordem;
	int i = vDestino;
	while (true) {
		ordem.push_back(djikstra[i]); 
		i = ordem[ordem.size() - 1];
		if (i == vOrigem) break; //trocar depois
	}
	cout << "Peso total: " << DistTotal << endl;
	cout << "Sequencia:\n";
	for (i = ordem.size() - 1; i >= 0; i--)
	{
		cout << ordem[i] << "-";
	}
	cout << vDestino << endl;
}

int main()
{
	/*auto* a1 = new Aresta(5, 0, 1);
	auto* a2 = new Aresta(1, 3, 0);
	auto* a3 = new Aresta(3, 0, 3);

	auto* a4 = new Aresta(1, 3, 1);
	auto* a5 = new Aresta(1, 4, 1);
	auto* a6 = new Aresta(3, 1, 2);

	auto* a7 = new Aresta(5, 2, 4);

	auto* a8 = new Aresta(1, 3, 4);
	auto* a9 = new Aresta(1, 4, 3);*/

	auto* a1 = new Aresta(1, 0, 4);
	auto* a2 = new Aresta(1, 4, 0);

	auto* a3 = new Aresta(3, 0, 1);
	auto* a4 = new Aresta(3, 1, 0);

	auto* a5 = new Aresta(4, 0, 2);
	auto* a6 = new Aresta(4, 2, 0);

	auto* a7 = new Aresta(1, 0, 3);
	auto* a8 = new Aresta(1, 0, 3);

	
	auto* a9 = new Aresta(1, 1, 2);
	auto* a10 = new Aresta(1, 2, 1);

	auto* a11 = new Aresta(4, 1, 3);
	auto* a12 = new Aresta(4, 3, 1);


	auto* a13 = new Aresta(5, 2, 3);
	auto* a14 = new Aresta(5, 3, 2);


	auto* a15 = new Aresta(1, 1, 4);
	auto* a16 = new Aresta(1, 4, 1);

	Grafo* grafo;
	grafo = Grafo::criarGrafo(5, 16, {a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16});

	int input  = 0;
	bool continuar = true;
	int origem = 0;
	int destino = 2;
	int dist = 0;
	//vector<int> res = grafo->dijkstra(origem, destino, dist);
//	grafo->proximaArestaEValida(4, a5);
	while (continuar)
	{
		cout << "Menu - Problema do Carteiro Chines\n";
		cout << "1 - Matriz de Custo\n";
		cout << "2 - Matriz de Roteamento\n";
		cout << "3 - Floyd\n";
		cout << "4 - Dijkstra";
		cout << "\n5 - Sair\n";
		cin >> input;
		switch (input)
		{
		case 1:
            //system("clear");
			cout << " -- Matriz de Custo --" << endl;
			exibirMatriz(grafo->mCusto);
			break;
		case 2:
            //system("clear");
            cout << " -- Matriz de Roteamento --" << endl;
            exibirMatriz(grafo->mRoteamento);
			break;
		case 3:
            //system("clear");
            grafo->algoritmoFloyd();
			break;
		case 4:
			//exibirDijkstra(res, origem, destino, dist);
            //exit(0);
		case 5:
			grafo->proximaArestaEValida(4, a5);
            //system("clear");
			continuar = false;
			break;
		default:
			break;
		}
	}
	
    return 0;
}

/*
 * algoritmo de fleury
    função Fleury(G = (V,E): grafo) : caminho
       G' := G     { G' = (V', E')}
       v0 := um vértice de G'
       C := [v0] {Inicialmente, o circuito contém só v0}
       Enquanto E' não vazio
           vi := último vértice de C
           Se vi tem só uma aresta incidente;
               ai := a aresta incidente a vi em G'
           Senão
               ai := uma aresta incidente a vi em G' e que não é uma ponte
           Retirar a aresta ai do grafo G'
           Acrescentar ai no final de C
           vj := vértice ligado a vi por ai
           Acrescentar vj no final de C
       Retornar C
 */