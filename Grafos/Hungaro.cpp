
#include "Hungaro.h"

#include <utility>

Hungaro::Hungaro(const vector<vector<int>>& matriz) {
    this->valoresOriginais = igualarLinhaColuna(matriz);
    this->valores = igualarLinhaColuna(clonarMatriz(matriz));

    this->linhasMatriz.resize(this->valores[0].size(), 0);
    this->colunasOcupadas.resize(this->valores[0].size(), 0);

    cout << "Matriz. " << endl;
    printarMatriz(this->valores);

    //Passo 1
    subtrairLinhaValorMinimo();
    //Passo 2
    subtrairColunaValorMinimo();
    //Passo 3
    cobrirZeros();
    //Passo 4
    while(this->numeroLinhas < this->valores.size())
    {
        criarZerosAdicionais();
        cobrirZeros();
    }

    optimizar();

    cout << "printando Matriz Riscos::: " << endl;
    printarMatriz(linhas);
    cout << "printando Matriz Valores::: " << endl;
    printarMatriz(valores);

    cout << endl << "Valor Total : " << getTotal() << endl;
}

vector<vector<int>> Hungaro::clonarMatriz(vector<vector<int>> matriz) {
    vector<vector<int>> clone = std::move(matriz);
    return clone;
}

void Hungaro::subtrairLinhaValorMinimo() {
    vector<int> menorValorLinha(this->valores.size(), -1);

    //Percorrendo a matriz para verificar o menor valor linha.
    for(int linha = 0; linha < this->valores.size(); linha++)
    {
        menorValorLinha[linha] = this->valores[linha][0]; //instanciando o primeiro valor como menor
        for(int col = 1; col < this->valores[0].size(); col++)
        {
            if(this->valores[linha][col] < menorValorLinha[linha])
                menorValorLinha[linha] = this->valores[linha][col];
        }
    }

    //Percorrendo matriz para realizar subtração do menor valor linha.
    for(int linha = 0; linha < this->valores.size(); linha++)
    {
        for(int col = 0; col < this->valores[0].size(); col++)
        {
            this->valores[linha][col] -= menorValorLinha[linha];
        }
    }

    cout << "Subtraindo por linha. " << endl;
    printarMatriz(this->valores);
}

void Hungaro::subtrairColunaValorMinimo() {
    vector<int> menorValorColuna(this->valores[0].size(), -1);

    //Percorrendo a matriz para verificar o menor valor coluna.
    for(int col = 0; col < this->valores[0].size(); col++)
    {
        menorValorColuna[col] = this->valores[0][col]; //primeiro valor como menor
        for(int linha = 1; linha < this->valores.size(); linha++)
        {
            if(this->valores[linha][col] < menorValorColuna[col])
                menorValorColuna[col] = this->valores[linha][col];
        }
    }

    //Percorrendo matriz para realizar subtração do menor valor coluna.
    for(int col = 0; col < this->valores.size(); col++)
    {
        for(int linha = 1; linha < this->valores.size(); linha++)
        {
            this->valores[linha][col] -= menorValorColuna[col];
        }
    }

    cout << "Subtraindo por coluna. " << endl;
    printarMatriz(this->valores);
}

void Hungaro::cobrirZeros() {
    this->numeroLinhas = 0;

    //Inicializando
    this->linhas = this->valores;

    for(int linha=0; linha < this->valores.size();linha++){
        for(int col=0; col < this->valores.size();col++){
            this->linhas[linha][col] = 0;
        }
    }

    for(int linha=0; linha < this->valores.size();linha++){
        for(int col=0; col < this->valores.size();col++){
            if(this->valores[linha][col] == 0)
                selecionarVizinhos(linha, col, maxVerticalHorizontal(linha, col));
        }
    }
}

/*Checa a direção (vertical | horizontal ) que contem mais zeros, para cada zero encontrado na vertical, o valor resultante é incrementado
para cada zero encontrado na horizontal, o valor resultante é subtraido.
o valor resultante será negativo(horizontal), zero(horizontal) ou positivo(vertical)*/

int Hungaro::maxVerticalHorizontal(int linha, int coluna) {
    int retorno = 0;
    for(int i=0; i < this->valores.size();i++){
        if(this->valores[i][coluna] == 0)
            retorno++;
        if(this->valores[linha][i] == 0)
            retorno--;
    }
    return retorno;
}

/* "risca" a matriz linha, os vizinhos do atual valor*/
void Hungaro::selecionarVizinhos(int linha, int coluna, int maximoVerticalHorizontal) {

    //Horizontal -1, vertical 1, intersecção 2;
    if(this->linhas[linha][coluna] == 2) // se ja foi riscada duas vezes (intersecção) não risca novamente.
        return;

    if(maximoVerticalHorizontal > 0 && this->linhas[linha][coluna] == 1) // se foi riscada verticalmente, não risca novamente
        return;

    if(maximoVerticalHorizontal <= 0 && this->linhas[linha][coluna] == -1) // se foi riscado horizontalmente não risca novamente
        return;

    for(int i=0; i < this->valores.size();i++){ // loop nos valores dos indices [linha][coluna] e os vizinhos respectivos
        if(maximoVerticalHorizontal > 0)	// se o valor maximoVerticalHorizontal for positivo, risca verticalmente
            this->linhas[i][coluna] = this->linhas[i][coluna] == -1 || this->linhas[i][coluna] == 2 ? 2 : 1; // se foi riscada antes da horizontal (-1), e precisa ser riscada na vertical (1), é uma intersecção (2). Caso contrario risca vertical.
        else			// se o valor maximoVerticalHorizontal é zero, risca horizontal.
            this->linhas[linha][i] = this->linhas[linha][i] == 1 || this->linhas[linha][i] == 2 ? 2 : -1; // se foi riscada antes da vertical (1) e precisa ser riscada na horizontal (-1), é uma intersecção (2). Caso contrario risca horizontal.
    }
    // incrementando o numero de linha
    this->numeroLinhas++;

}

void Hungaro::criarZerosAdicionais() {
    int menorValorNaoRiscado = 0;

    //procura o valor minimo nos numeros não riscados
    for(int linha=0; linha < this->valores.size();linha++){
        for(int col=0; col < this->valores.size();col++){
            if(this->linhas[linha][col] == 0 && (this->valores[linha][col] < menorValorNaoRiscado || menorValorNaoRiscado == 0))
                menorValorNaoRiscado = this->valores[linha][col];
        }
    }

    // Subtrai o minimo dos valores não riscados, e então adiciona os elementos riscados duas vezes
    for(int linha=0; linha < this->valores.size();linha++){
        for(int col=0; col < this->valores.size();col++){
            if(this->linhas[linha][col] == 0) // Se não estiver riscado, subtrai
                this->valores[linha][col] -= menorValorNaoRiscado;

            else if(this->linhas[linha][col] == 2) // Se estiver riscado 2 vezes (intersecção), adiciona
                this->valores[linha][col] += menorValorNaoRiscado;
        }
    }

    printarMatriz(valores);
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
        coluna.reserve(matriz.size());
        for (int i = 0; i < matriz.size(); i++) {
            coluna.push_back(0);
        }
        matriz.push_back(coluna);
    }
    return matriz;
}

bool Hungaro::optimizar(int linha) {
    if(linha == this->linhasMatriz.size()) // se todas linhas ja forem designadas
        return true;

    for(int col=0; col<valores.size();col++){ // Tenta todas colunas
        if(this->valores[linha][col] == 0 && this->colunasOcupadas[col] == 0){ // Se o valor atual na coluna 'col' é zero e não está ocupada
            this->linhasMatriz[linha] = col; // Atribui a linha com o valor da coluna
            this->colunasOcupadas[col] = 1; // Marca a coluna como ocupada
            if(optimizar(linha+1)) // Se as proximas linhas foram atribuidas com sucesso em uma unica coluna.
                return true;
            this->colunasOcupadas[col] = 0; // Se as proximas linhas não possuem valor, retorna e tenta as outras.
        }
    }
    return false;
}

bool Hungaro::optimizar() {
    return optimizar(0);
}

int Hungaro::getTotal() {
    int total = 0;
    for(int i = 0; i < this->valores.size(); i++)
    {
        total+= this->valoresOriginais[i][this->linhasMatriz[i]];
        cout << endl << this->valoresOriginais[i][this->linhasMatriz[i]];
    }


    return total;
}
