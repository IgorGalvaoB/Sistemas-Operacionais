#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define _GNU_SOURCE

int*a,b;

int main(int argc,char *argv[]) {
    int n = atoi(argv[1]);
    int num_proc;
    int i;
    pthread_t tid[n];
    pthread_attr_t attr;

    a = (int *) malloc(sizeof(int)*n);
    printf("Vetor A = [");
    srand(time(NULL));
    for(i=0;i<n;i++){
        a[i] = rand()%100;
        printf("%d",a[i]);
    }

    num_proc = sysconf(_SC_NPROCESSORS_ONLN);

    return 0;
}
