#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<iostream>


int main(){
    pid_t pid, pid1;
    pid = fork();
    if(pid==0){
        pid1=getpid();
        printf("Filho: pid %d\n",pid);
        //0
        printf("FILHO: pid1 %d\n",pid1);
        //x
    }else{
        pid1 = getpid();
        printf("Pai: pid=%d\n",pid);
        //x
        printf("pai: pid1=%d\n",pid1);
        //x-1
    }
    return 0;
}
