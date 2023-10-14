#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<string>

using namespace std;
vector<vector<int>> randomizarMatriz(int linhas, int colunas) {
    vector<vector<int> > matriz(linhas,vector<int>(colunas));
    for(int i = 0; i<linhas;i++){
        for(int j = 0;j<colunas;j++){
            matriz[i][j] = rand()%101;
        }
    }
    return matriz;
}


void salvarArquivo(const vector<vector<int> >& matriz, const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);
    if(arquivo.is_open()){
        for(int i =0; i<matriz.size();i++){
            for(int j = 0; j<matriz[i].size();j++){
                if(j == matriz[i].size()-1){
                    arquivo<<matriz[i][j]<<'\n';
                }else{
                    arquivo << matriz[i][j] << ' ';
                }
            }
        
        }
        arquivo.close();
    }else{
        runtime_error("o arquivo não pôde ser feito");
    }
} 

int main(int argc, char *argv[]) {
    if(argc !=5){
        cout<<"Quantidade de argumentos incorreta"<<endl;
        return 1;
    }
    int linha1, linha2,coluna1,coluna2;
    linha1 = atoi(argv[1]);
    coluna1 = atoi(argv[2]);
    linha2 = atoi(argv[3]);
    coluna2 = atoi(argv[4]);

    if(coluna1!=linha2){
        cout<<"As matrizes não podem ser multiplicadas"<<endl;
        return 2;
    }

    srand(time(NULL));
    
    vector<vector<int> > matriz1 = randomizarMatriz(linha1,coluna1);
    vector<vector<int> > matriz2 = randomizarMatriz(linha2,coluna2);
        
    salvarArquivo(matriz1,"matriz1.txt");
    salvarArquivo(matriz2,"matriz2.txt");
    
    return 0;
}

