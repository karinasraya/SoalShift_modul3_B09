#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void* hitung(void *args){
	int b=strtol((char*)args,NULL,10);
	int hasil=1;
	if(b<0){
		printf("ERROR!\n");
	}
	else{
	for(int i=1;i<=b;i++){
		hasil*=i;
	}
	printf("%d! = %d\n",b,hasil);
	}
}

int main(int argc, char** args){
	pthread_t tid[argc-1];
	for(int i=0;i<argc-1;i++){
		pthread_create(&(tid[i]),NULL,&hitung,(void*)args[i+1]);
	}
	for(int i=0;i<argc-1;i++){
		pthread_join(tid[i],NULL);
	}
}
