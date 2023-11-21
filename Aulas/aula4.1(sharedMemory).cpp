#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<iostream>


void implementacao1(int *a){
    *a = *a+1;
    printf("executando filho 1 = %d\n",getpid());

}
void implementacao2(int *a){
    *a = *a*2;
    printf("executando filho 2 = %d\n",getpid());
    
}
int main()
{
    int filho1,filho2,status,i;
    int* mem;
    void* a;
    int valor = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | 0666);

    a = shmat(valor,NULL,0);
    mem = (int*)a;
  
    *mem = 5;
    filho1 = fork();
    if(filho1 > 0){
        filho2=fork();
    }
    if(filho1 == 0 ){
        //sleep(1);
        implementacao1(mem);
        printf("Filho 1 finalizou (PID=%d) e o valor do inteiro é: %d\n",getpid(),*mem);
        shmdt(mem);
        exit(EXIT_SUCCESS);
    }else if(filho2 == 0){
        sleep(0.2);
        implementacao2(mem);
        printf("Filho 2 finalizou (PID=%d) e o valor do inteiro é: %d\n",getpid(),*mem);
        shmdt(mem);
        exit(EXIT_SUCCESS);
    }
    waitpid(filho1,&status,0);
    waitpid(filho2,NULL,0);
    if(WIFEXITED(status)){
        printf("%d\n", WEXITSTATUS(status));
    }
    printf("%d\n",*mem);
    shmctl(valor, IPC_RMID,NULL);
    return 0;
}
