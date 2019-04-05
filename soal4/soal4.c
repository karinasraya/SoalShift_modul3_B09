#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

struct proses{
	int pros, high;
};

void* simpan(void* args);
void* unzip(void* args);

int main(){
	int file=2;
	pthread_t tid[100];
	struct proses P;
	P.pros=0;
	P.high=10;

	for(int i=1;i<=file;i++){
		P.pros=i;
		pthread_create(&tid[i],NULL,&simpan,(void*)&P);
		P.high+=10;
	}

	for(int i=1;i<=file;i++){
		pthread_join(tid[i],NULL);
	}
	
	sleep(15);

	for(int i=1;i<=file;i++){
		P.pros=i;
		pthread_create(&tid[i],NULL,&unzip,(void*)&P);
	}
}

void* simpan(void* args){
	char command[100];
	struct proses*extract=(struct proses*)args;

	sprintf(command,"mkdir /Documents/FolderProses%d",extract->pros);
	system(command);

	strcpy(command,"");
	sprintf(command,"ps aux --no-heading | head -%d | tail -%d> /Document/FolderProses%d/SimpanProses%d.txt",extract->high,10,extract->pros,extract->pros);
	system(command);

	strcpy(command,"");
	sprintf(command,"zip -qmj /Documents/FolderProses%d/KompresProses%d /Documents/FolderProses%d/SimpanProses%d.txt",extract->pros,extract->pros,extract->pros,extract->pros);
	system(command);
}

void* unzip(void* args){
	char command[100];
	struct proses*extract=(struct proses*)args;
	strcpy(command,"");
	sprintf(command,"unzip -qd /Documents/FolderProses%d /Documents/FolderProses%d/KompresProses%d.zip", extract->pros, extract->pros, extract->pros);
	system(command);
}
