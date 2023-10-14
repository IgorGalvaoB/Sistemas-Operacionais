#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include<thread>
#include<chrono>

using namespace std;
void multiplicador(vector<vector<int>> &resultado,const vector<vector<int>> &matriz1, const vector<vector<int>> &matriz2,int inicio,int fim,int contador)
{    
    auto inicioTime = chrono::high_resolution_clock::now();

    int linhas1 = matriz1.size();
    int colunas1 = matriz1[0].size();
    int colunas2 = matriz2[0].size();
    string nomeArquivo = "paraleloThread" + to_string(contador+1)+".txt";
    ofstream arquivo(nomeArquivo);
    arquivo<< linhas1 << "x" << colunas2<<endl; 
        for (int i = inicio; i < fim; i++)
        {
            for (int j = 0; j < colunas2; j++)
            {
                for (int k = 0; k < colunas1; k++)
                {
                    resultado[i][j] += matriz1[i][k] * matriz2[k][j];

                }
                arquivo<< 'C'<<i<<'*'<<j<<' '<<resultado[i][j]<<endl;
            }
        }
    auto fimTime = chrono::high_resolution_clock::now();
    auto duracao = chrono::duration_cast<std::chrono::milliseconds>(fimTime - inicioTime);
    arquivo<<duracao.count()<<"ms"<<endl;
    cout<<"Thread"<< contador << " Tempo:"<<duracao.count()<<"ms"<<endl;

}
int main(int argc, char *argv[])
{
    auto inicio = chrono::high_resolution_clock::now();

    if (argc != 4)
    {
        cout << "Quantidade de argumentos incorreta" << endl;
        return 1;
    }

    ifstream arquivoMatriz1,arquivoMatriz2;

    arquivoMatriz1.open(argv[1]);
    arquivoMatriz2.open(argv[2]);
    int P = stoi(argv[3]);
    
    if (!arquivoMatriz1.is_open() || !arquivoMatriz2.is_open())
    {
        cout << "algum arquivo não pôde ser lido" << endl;
        return 2;
    }

    vector<vector<int> > matriz1, matriz2;
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
    int linhas1 = matriz1.size();
    int colunas1 = matriz1[0].size();
    int colunas2 = matriz2[0].size();
   
    
    vector<thread> threads;
    vector<vector<int>> resultado(linhas1,vector<int>(colunas2, 0));

    
    for (int i = 0; i < P; i++) {

     
        
        int inicio = (i*linhas1)/P;
        int fim = ((i+1)*linhas1)/P;
        
        threads.emplace_back(multiplicador,ref(resultado),ref(matriz1),ref(matriz2),inicio,fim,i);
           
 

        
       
    } 

    for (thread& thread : threads) {
        thread.join();
    } 
    auto fim = chrono::high_resolution_clock::now();
    auto duracao = chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
    
    cout << "Tempo de execução: " << duracao.count() << "milisegundos" << std::endl;
   

    return 0;
}
