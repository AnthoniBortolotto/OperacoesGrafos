
#include "Hungaro.h"

#include <utility>

Hungaro::Hungaro(vector<vector<int>> matriz) {
    this->valoresOriginais = igualarLinhaColuna(matriz);
    valores = igualarLinhaColuna(clonarMatriz(matriz));

    printarMatriz(valores);
    linhasMatriz.resize(valores[0].size(), -1);
    colunasOcupadas.resize(valores[0].size(), -1);

    //Passo 1
    subtrairLinhaValorMinimo();
    //Passo 2
    subtrairColunaValorMinimo();
    //Passo 3
    cobrirZeros();
    //Passo 4
    while(numeroLinhas < valores.size())
    {
        criarZerosAdicionais();
        cobrirZeros();
    }

    optimizar();

    cout << "printando::: " << endl;
    printarMatriz(valores);
    cout << "TOTAL " << getTotal();
}

vector<vector<int>> Hungaro::clonarMatriz(vector<vector<int>> matriz) {
    vector<vector<int>> clone = std::move(matriz);
    return clone;
}

void Hungaro::subtrairLinhaValorMinimo() {
    vector<int> menorValorLinha(valores.size(), -1);

    //Percorrendo a matriz para verificar o menor valor linha.
    for(int linha = 0; linha < valores.size(); linha++)
    {
        menorValorLinha[linha] = valores[linha][0]; //instanciando o primeiro valor como menor
        for(int col = 1; col < valores[0].size(); col++)
        {
            if(valores[linha][col] < menorValorLinha[linha])
                menorValorLinha[linha] = valores[linha][col];
        }
    }

    //Percorrendo matriz para realizar subtração do menor valor linha.
    for(int linha = 0; linha < valores.size(); linha++)
    {
        for(int col = 0; col < valores[0].size(); col++)
        {
            valores[linha][col] -= menorValorLinha[linha];
        }
    }
}

void Hungaro::subtrairColunaValorMinimo() {
    vector<int> menorValorColuna(valores[0].size(), -1);

    //Percorrendo a matriz para verificar o menor valor coluna.
    for(int col = 0; col < valores[0].size(); col++)
    {
        menorValorColuna[col] = valores[0][col]; //primeiro valor como menor
        for(int linha = 1; linha < valores.size(); linha++)
        {
            if(valores[linha][col] < menorValorColuna[col])
                menorValorColuna[col] = valores[linha][col];
        }
    }

    //Percorrendo matriz para realizar subtração do menor valor coluna.
    for(int col = 0; col < valores[0].size(); col++)
    {
        for(int linha = 1; linha < valores.size(); linha++)
        {
            valores[linha][col] -= menorValorColuna[col];
        }
    }

}

void Hungaro::cobrirZeros() {
    numeroLinhas = 0;

    //Inicializando
    linhas = valores;
    for(int linha=0; linha<valores.size();linha++){
        for(int col=0; col<valores[0].size();col++){
            linhas[linha][col] = 0;
        }
    }


    for(int linha=0; linha<valores.size();linha++){
        for(int col=0; col<valores[0].size();col++){
            if(valores[linha][col] == 0)
                selecionarVizinhos(linha, col, maxVerticalHorizontal(linha, col));
        }
    }
}

/*Checa a direção (vertical | horizontal ) que contem mais zeros, para cada zero encontrado na vertical, o valor resultante é incrementado
para cada zero encontrado na horizontal, o valor resultante é subtraido.
o valor resultante será negativo(horizontal), zero(horizontal) ou positivo(vertical)*/

int Hungaro::maxVerticalHorizontal(int linha, int coluna) {
    int retorno = 0;
    for(int i=0; i<valores.size();i++){
        if(valores[i][coluna] == 0)
            retorno++;
        if(valores[linha][i] == 0)
            retorno--;
    }
    return retorno;
}

/* "risca" a matriz linha, os vizinhos do atual valor*/
void Hungaro::selecionarVizinhos(int linha, int coluna, int maximoVerticalHorizontal) {

    //Horizontal -1, vertical 1, intersecção 2;
    if(linhas[linha][coluna] == 2) // se ja foi riscada duas vezes (intersecção) não risca novamente.
        return;

    if(maximoVerticalHorizontal > 0 && linhas[linha][coluna] == 1) // se foi riscada verticalmente, não risca novamente
        return;

    if(maximoVerticalHorizontal <= 0 && linhas[linha][coluna] == -1) // se foi riscado horizontalmente não risca novamente
        return;

    for(int i=0; i<valores.size();i++){ // loop nos valores dos indices [linha][coluna] e os vizinhos respectivos
        if(maximoVerticalHorizontal > 0)	// se o valor maximoVerticalHorizontal for positivo, risca verticalmente
            linhas[i][coluna] = linhas[i][coluna] == -1 || linhas[i][coluna] == 2 ? 2 : 1; // se foi riscada antes da horizontal (-1), e precisa ser riscada na vertical (1), é uma intersecção (2). Caso contrario risca vertical.
        else			// se o valor maximoVerticalHorizontal é zero, risca horizontal.
            linhas[linha][i] = linhas[linha][i] == 1 || linhas[linha][i] == 2 ? 2 : -1; // se foi riscada antes da vertical (1) e precisa ser riscada na horizontal (-1), é uma intersecção (2). Caso contrario risca horizontal.
    }
    // incrementando o numero de linha
    numeroLinhas++;
}

void Hungaro::criarZerosAdicionais() {
    int menorValorNaoRiscado = 0;

    //procura o valor minimo nos numeros não descobertos
    for(int linha=0; linha<valores.size();linha++){
        for(int col=0; col<valores[0].size();col++){
            if(linhas[linha][col] == 0 && (valores[linha][col] < menorValorNaoRiscado || menorValorNaoRiscado == 0))
                menorValorNaoRiscado = valores[linha][col];
        }
    }

    // Subtrai o minimo dos valores não riscados, e então adiciona os elementos riscados duas vezes
    for(int linha=0; linha<valores.size();linha++){
        for(int col=0; col<valores[0].size();col++){
            if(linhas[linha][col] == 0) // If uncovered, subtract
                valores[linha][col] -= menorValorNaoRiscado;

            else if(linhas[linha][col] == 2) // If covered twice, add
                valores[linha][col] += menorValorNaoRiscado;
        }
    }

}

void Hungaro::printarMatriz(vector<vector<int>> matriz) {
    for(int linha=0; linha<matriz.size();linha++){
        for(int col=0; col<matriz[0].size();col++){
            cout << matriz[linha][col] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> Hungaro::igualarLinhaColuna(vector<vector<int>> matriz) {
    if (matriz[0].size() == matriz.size()) return matriz;
    else if (matriz[0].size() > matriz.size()) {
        for (int i = 0; i < matriz.size(); ++i) {
            matriz.resize(matriz[0].size(), vector<int>(matriz[0].size(), 0));
        }
    }
    else
    {
        vector<int> coluna;
        for (int i = 0; i < matriz.size(); i++) {
            coluna.push_back(0);
        }
        matriz.push_back(coluna);
    }
    return matriz;
}

bool Hungaro::optimizar(int linha) {

}

bool Hungaro::optimizar() {
    return optimizar(0);
}

int Hungaro::getTotal() {
    int total = 0;
    for(int i = 0; i < valores.size(); i++)
    {
        cout << linhasMatriz[i] << endl;
    }

    return total;
}
