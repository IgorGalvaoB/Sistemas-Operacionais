#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];  // Array para os descritores de arquivo do pipe
    pid_t pid;
    pipe(pipe_fd);
    // Criar o pipe
    if (pipe(pipe_fd) == -1) {
        perror("Erro ao criar o pipe");
        exit(EXIT_FAILURE);
    }

    // Criar um novo processo
    pid = fork();

    if (pid == -1) {
        perror("Erro ao criar o processo filho");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Processo pai
        close(pipe_fd[0]);  // Fecha a extremidade de leitura do pipe no processo pai

        // Escrever dados no pipe
        const char mensagem_pai[] = "Olá, filho!";
        write(pipe_fd[1], mensagem_pai, sizeof(mensagem_pai));

        close(pipe_fd[1]);  // Fechar a extremidade de escrita do pipe no processo pai
    } else {
        // Processo filho
        close(pipe_fd[1]);  // Fecha a extremidade de escrita do pipe no processo filho
   
        // Ler dados do pipe
        char buffer[100];
        ssize_t bytes_lidos = read(pipe_fd[0], buffer, sizeof(buffer));

        if (bytes_lidos == -1) {
            perror("Erro ao ler do pipe");
            exit(EXIT_FAILURE);
        }

        printf("Filho recebeu: %s\n", buffer);

        close(pipe_fd[0]);  // Fechar a extremidade de leitura do pipe no processo filho
    }

    return 0;
}
