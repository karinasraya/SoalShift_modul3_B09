#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

struct proses{
	int pros, max;
};

void* simpan(void* args);
void* unzip(void* args);

int main(){
	pthread_t tid[100];
	struct proses P;
	P.pros=0;
	P.max=10;

	for(int i=0;i<2;i++){
		P.pros=i+1;
		pthread_create(&tid[i+1],NULL,&simpan,(void*)&P);
		pthread_join(tid[i+1],NULL);
		P.max+=10;
	}

	sleep(15);

	for(int i=0;i<2;i++){
		P.pros=i+1;
		pthread_create(&tid[i+1],NULL,&unzip,(void*)&P);
		pthread_join(tid[i+1],NULL);
	}
}

void* simpan(void* args){
	char ekse[100];
	char buat[1000]="mkdir /home/karinasraya/Documents/FolderProses%d";
	char ambil[1000]="ps -aux | head -%d | tail -%d > /home/karinasraya/Documents/FolderProses%d/SimpanProses%d.txt";
	char zip[1000]="zip -qmj /home/karinasraya/Documents/FolderProses%d/KompresProses%d /home/karinasraya/Documents/FolderProses%d/SimpanProses%d.txt";

	struct proses*extract=(struct proses*)args;

	sprintf(ekse,buat,extract->pros);
	system(ekse);

	strcpy(ekse,"");
	sprintf(ekse,ambil,extract->max,10,extract->pros,extract->pros);
	system(ekse);

	strcpy(ekse,"");
	sprintf(ekse,zip,extract->pros,extract->pros,extract->pros,extract->pros);
	system(ekse);
}

void* unzip(void* args){
	char ekse[100];
	char unzip[1000]="unzip -qd /home/karinasraya/Documents/FolderProses%d /home/karinasraya/Documents/FolderProses%d/KompresProses%d.zip";

	struct proses*extract=(struct proses*)args;

	strcpy(ekse,"");
	sprintf(ekse,unzip, extract->pros, extract->pros, extract->pros);
	system(ekse);
}
