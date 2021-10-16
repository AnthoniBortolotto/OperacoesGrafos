//bibliotecas que o algoritmo usa
#include <iostream>
#include <vector>
#include "Aresta.h"
#include "Grafo.h"

using namespace std;

//Declaração da função que mostra o djikstra
void exibirDijkstra(Grafo* grafo, vector<int> djikstra, int vOrigem, int vDestino);

int main() //função chamada quando abre o programa
{
	//questão 3
	//declaração de variaveis
	int input  = 0;
	bool continuar = true;
	int origem = 0;
	int destino = 2;
	int dist = 0;
	//criação das arestas
	auto* a1 = new Aresta(10, 0, 1);
	auto* a2 = new Aresta(5, 0, 4);

	auto* a3 = new Aresta(1, 1, 2);
	auto* a4 = new Aresta(3, 1, 4);

	auto* a5 = new Aresta(4, 2, 3);

	auto* a6 = new Aresta(7, 3, 0);
	auto* a7 = new Aresta(6, 3, 2);

	auto* a8 = new Aresta(2, 4, 3);
	auto* a9 = new Aresta(9, 4, 2);
	auto* a10 = new Aresta(2, 4, 1);

	Grafo* grafo;
	int numV = 5;
	int numA = 10;
	grafo = Grafo::criarGrafo(numV, numA, { a1, a2, a3, a4, a5, a6, a7, a8, a9, a10 });
	vector<int> res;

	while (continuar)
	{
		cout << "Menu - TDE\n";
		cout << "1 - resolver questao 3\n";
		cout << "2 - Sair\n";
		cin >> input;
		switch (input)
		{
		case 1:
			res = grafo->dijkstra(0);
				for (int j = 0; j < numV; j++)
				{
					cout << "melhor percurso do vertice " << 1;
					cout << " ate " << j + 1 << endl;
					
					exibirDijkstra(grafo, res, 0, j);
				}
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

void exibirDijkstra(Grafo* grafo, vector<int> djikstra, int vOrigem, int vDestino) { //refatorar com o traduzirDijkstra
	vector<int> ordem;
	int i = vDestino;
	if (vOrigem != vDestino) {
		while (true) {
			ordem.push_back(djikstra[i]);
			i = ordem[ordem.size() - 1];
			if (i == vOrigem) break; //trocar depois
		}
	}

	cout << "Peso total: " << grafo->obterDistDijkstra(djikstra, vOrigem, vDestino) << endl;
	cout << "Sequencia:\n";
	for (i = ordem.size() - 1; i >= 0; i--)
	{
		cout << ordem[i] + 1 << "-"; //pra ficar igual o grafo
	}
	cout << vDestino + 1 << endl;
}