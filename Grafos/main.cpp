
#include <iostream>
#include <vector>
#include "Hungaro.h"
#include "Aresta.h"
#include "Grafo.h"

using namespace std;

void exibirMatriz(const vector<vector<int>>& matriz) {
	for (vector<int> i : matriz)
	{
		for (int j : i)
		{
			cout << j << " ";
		}
		cout << "\n";
	}
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
		cout << ordem[i]+1 << "-"; //pra ficar igual o grafo
	}
	cout << vDestino+1 << endl;
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

	/*auto* a1 = new Aresta(1, 0, 4);
	auto* a2 = new Aresta(1, 4, 0);

	auto* a3 = new Aresta(3, 0, 1);
	auto* a4 = new Aresta(3, 1, 0);

	auto* a5 = new Aresta(4, 0, 2);
	auto* a6 = new Aresta(4, 2, 0);

	auto* a7 = new Aresta(1, 0, 3);
	auto* a8 = new Aresta(1, 3, 0);

	
	auto* a9 = new Aresta(1, 1, 2);
	auto* a10 = new Aresta(1, 2, 1);

	auto* a11 = new Aresta(4, 1, 3);
	auto* a12 = new Aresta(4, 3, 1);


	auto* a13 = new Aresta(5, 2, 3);
	auto* a14 = new Aresta(5, 3, 2);


	auto* a15 = new Aresta(1, 1, 4);
	auto* a16 = new Aresta(1, 4, 1);*/

	//questão 3
	int input  = 0;
	bool continuar = true;
	int origem = 0;
	int destino = 2;

	/*auto* a1 = new Aresta(10, 0, 1);
	auto* a2 = new Aresta(5, 0, 4);

	auto* a3 = new Aresta(1, 1, 2);
	auto* a4 = new Aresta(3, 1, 4);

	auto* a5 = new Aresta(4, 2, 3);

	auto* a6 = new Aresta(7, 3, 0);
	auto* a7 = new Aresta(6, 3, 2);

	auto* a8 = new Aresta(2, 4, 3);
	auto* a9 = new Aresta(9, 4, 2);
	auto* a10 = new Aresta(2, 4, 1);*/
	
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
	//vector<int> res = grafo->dijkstra(origem, destino, dist);
//	grafo->proximaArestaEValida(4, a5);

    //
    // METODO HUNGARO DO SATANAS
   /* vector<vector<int>> matrizHungaro {{10,4,8,6},
                                       {6,4,9,10},
                                       {6,7,8,9}};

    Hungaro hungaro(matrizHungaro);*/
    //     L1, L2, L3, L4
    /* E1,
     * E2,
     * E3
     *
     * Uma fábrica possui quatro locais L1, L2, L3 e L4 para receber três novos equipamentos (E1,
        E2, E3). A operação desses equipamentos gera um fluxo de materiais cujo custo de manuseio
        depende do local da instalação e, estão no quadro a seguir:
     */
	while (continuar)
	{
		cout << "Menu - Problema do Carteiro Chines\n";
		cout << "1 - Floyd\n";
		cout << "2 - Dijkstra";
		cout << "\n3 - Fleury\n";
		cout << "4 - resolver questao 3\n";
		cout << "5 - Sair\n";
		cin >> input;
		switch (input)
		{
		case 1:
            grafo->algoritmoFloyd();
			break;
		case 2:
			exibirDijkstra(grafo, grafo->dijkstra(origem, destino), origem, destino);
			break;
		case 3:
			grafo->fleury(0);
			break;
		case 4:
			
			for (int i = 0; i < numV; i++) {
				for (int j = 0; j < numV; j++)
				{
					cout << "melhor percurso do vertice " << i + 1;
					cout << " ate " << j + 1 << endl;
					res = grafo->dijkstra(i, j);
					exibirDijkstra(grafo, res, i, j);
				}
			}
			

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