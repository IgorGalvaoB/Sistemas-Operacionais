#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>


std::vector<std::vector<int>> gerarMatrizAleatoria(int n, int m) {
    
    std::srand(std::time(NULL));


    std::vector<std::vector<int>> matriz(n, std::vector<int>(n));


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matriz[i][j] = std::rand() % 101;
        }
    }

    return matriz;
}

std::vector<std::vector<int>> multiplicarMatrizes(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, int inicio, int fim){

    int linhasA = A.size();
    int colunasA = A[0].size();
    int colunasB = B[0].size();

    // Inicializar a matriz resultante com zeros
    std::vector<std::vector<int>> matrizC(linhasA, std::vector<int>(colunasB, 0));

    for (int i = 0; i < linhasA; ++i) {
        for (int j = 0; j < colunasB; ++j) {
            for (int k = 0; k < colunasA; ++k) {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }

}




int main(){
    return 0;
}