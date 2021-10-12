
#include <vector>
#include <iostream>

using namespace std;

class Hungaro {
public:
    explicit Hungaro(const vector<vector<int>>& matriz);

private:
    vector<vector<int>> valoresOriginais;
    vector<vector<int>> valores;
    vector<vector<int>> linhas;
    int numeroLinhas{};
    vector<int> linhasMatriz;
    vector<int> colunasOcupadas;
    static vector<vector<int>> clonarMatriz(vector<vector<int>> matriz);

    //Funcoes
    void subtrairLinhaValorMinimo();
    void subtrairColunaValorMinimo();
    void cobrirZeros();

    int maxVerticalHorizontal(int linha, int coluna);

    void selecionarVizinhos(int linha, int coluna, int maximoVerticalHorizontal);
    void criarZerosAdicionais();

    static void printarMatriz(vector<vector<int>> matriz);
    bool optimizar(int linha);
    bool optimizar();
    static vector<vector<int>> igualarLinhaColuna(vector<vector<int>> matriz);

    int getTotal();
};
