
#include <iostream>
#include <vector>
#include "Grafo.h"
#include "Aresta.h"

using namespace std;

int main()
{
    auto* a1 = new Aresta(1, "v1", "v2");
    auto* a2 = new Aresta(4, "v2", "v3");
    auto* a3 = new Aresta(2, "v2", "v3");
    auto* a4 = new Aresta(2, "v1", "v3");
    auto* a5 = new Aresta(1, "v3", "v4");

    Grafo::criarGrafo(4,5, {a1,a2,a3,a4,a5});

	int input;
	bool continuar = true;
	while (continuar)
	{
		cout << "Menu\n 1- Problema do carteiro chines\n5-sair\n";
		cin >> input;
		switch (input)
		{
		case 1:
            ;
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
