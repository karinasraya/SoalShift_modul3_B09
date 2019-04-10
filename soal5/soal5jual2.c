#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>
#include<ctype.h>
#include<termios.h>
#include <sys/ipc.h>
#include <sys/shm.h>


key_t key = 1234;
int *gudang;

char getch(){
    /*#include <unistd.h>   //_getch*/
    /*#include <termios.h>  //_getch*/
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 }


void* cene3(void *arg)
{
    while(1)
    {
	    
            
            
                system("clear");
                printf("scene Toko versi Penjual\n");
                printf("Stock Toko:%d\n",*gudang);
                printf("Masukkan pilihan\n");
                printf("1.Restock\n2.Back\n");
                sleep(1);
            
            
        
        
    }
	return NULL;
}

pthread_t tid[10];

 int main()
 {
     int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        gudang = shmat(shmid, NULL, 0);
        *gudang=0;

    char cmd;

int err;

        err=pthread_create(&(tid[0]),NULL,&cene3,NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}



    while(1)
    {
        
        cmd=getch();
        if(cmd=='1')
        {
            *gudang = *gudang + 1;
        }
        else
        {
            break;
        }
        
    }

    shmdt(gudang);
    shmctl(shmid, IPC_RMID, NULL);
        return 0;
 }