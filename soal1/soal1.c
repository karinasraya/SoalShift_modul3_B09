#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void* hitung(void *args){
	int *b=(int *)args;
	int hasil=1;
	if(b<0){
		printf("ERROR!\n");
	}
	else{
	for(int i=1;i<=*b;i++){
		hasil*=i;
	}
	printf("%d! = %d\n",*b,hasil);
	}
}

int main(int argc, char *args[]){
	pthread_t tid[argc-1];
	int konfersi[100];

	for(int i=0;i<argc-1;i++){
		konfersi[i]=atoi(args[i+1]);
	}

	for(int i=0;i<argc-2;i++){
		for(int j=0;j<(argc-i-2);j++){
		if(konfersi[j]<konfersi[j+1]){
			int temp=konfersi[j];
			konfersi[j]=konfersi[j+1];
			konfersi[j+1]=temp;
		}
		}
	}

	for(int i=0;i<argc-1;i++){
		pthread_create(&(tid[i]),NULL,&hitung,(void*)&konfersi[i]);
	}

	for(int i=0;i<argc-1;i++){
		pthread_join(tid[i],NULL);
	}
}
