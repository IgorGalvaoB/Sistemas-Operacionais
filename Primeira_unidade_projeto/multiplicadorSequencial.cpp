#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

vector<vector<int> > multiplicador(const vector<vector<int> > &matriz1, const vector<vector<int> > &matriz2)
{
    int linhas1 = matriz1.size();
    int colunas1 = matriz1[0].size();
    int colunas2 = matriz2[0].size();

    vector<vector<int> > resultado(linhas1, vector<int>(colunas2, 0));

    for (int i = 0; i < linhas1; i++)
    {
        for (int j = 0; j < colunas2; j++)
        {
            for (int k = 0; k < colunas1; k++)
            {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
 
    return resultado;
}

void arquivoResultado(const vector<vector<int> > &matrizResultado,const int tempo)
{
    ofstream arquivo("resultadoSequencial.txt");
    arquivo<< matrizResultado.size()<< ' '<<matrizResultado[0].size()<<endl;
    for(int i =0; i<matrizResultado.size();i++){
        for(int j = 0; j< matrizResultado[i].size();j++){
            arquivo<< 'C'<<i<<'*'<<j<<' '<<matrizResultado[i][j]<<endl;
        }
        
    }
    arquivo<<tempo;
    arquivo.close();
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        cout << "Quantidade de argumentos incorreta" << endl;
        return 1;
    }

    ifstream arquivoMatriz1,arquivoMatriz2;

    arquivoMatriz1.open(argv[1]);
    arquivoMatriz2.open(argv[2]);

    if (!arquivoMatriz1.is_open() || !arquivoMatriz2.is_open())
    {
        cout << "algum arquivo não pôde ser lido" << endl;
        return 2;
    }

    vector<vector<int> > matriz1, matriz2,resultado;
    vector<int> linha;
    int valor;
    while(arquivoMatriz1>>valor){
        linha.push_back(valor);
        if(arquivoMatriz1.peek()=='\n'){
            matriz1.push_back(linha);
            linha.clear();
        }
    }
    arquivoMatriz1.close();
    while(arquivoMatriz2>>valor){
        linha.push_back(valor);
        if(arquivoMatriz2.peek()=='\n'){
            matriz2.push_back(linha);
            linha.clear();
        }
    }
    arquivoMatriz2.close();
  
    auto inicio = chrono::high_resolution_clock::now();
    resultado = multiplicador(matriz1,matriz2);
    auto fim = chrono::high_resolution_clock::now();
    auto duracao = chrono::duration_cast<std::chrono::microseconds>(fim - inicio);

    cout << "Tempo de execução: " << duracao.count() << "milliseconds" << std::endl;
    arquivoResultado(resultado,duracao.count());
    
    return 0;
}
