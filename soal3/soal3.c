#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[3];
int sirajloop=0;
int akmalloop=0;

int* sl = &sirajloop;
int* al = &akmalloop;

void* playandcount1(void *arg)
{
	while(1)
    {
        if(*sl ==3)
        {
            printf("Siraj ayo tidur tidak dapat digunakan dalam 10 detik\n");
            sleep(10);
            *sl = 0;
        }
    }
	return NULL;
}

void* playandcount2(void *arg)
{
	while(1)
    {
        if(*al ==3)
        {
            printf("Aqmal ayo bangun tidak dapat digunakan dalam 10 detik\n");
            sleep(10);
            *al = 0;
        }
    }
	return NULL;
}

typedef struct 
{
    int WakeUp_Status;
}akmal;

typedef struct 
{
    int Spirit_Status;
}siraj;

siraj a;
akmal b;
 
int main()
{
    //Inisiasi
    a.Spirit_Status = 100;
    b.WakeUp_Status = 0;

    siraj *ptra = &a;
    akmal *ptrb = &b;

//inisiasi thread
    
    int err=pthread_create(&(tid[0]),NULL,&playandcount1,NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
    int err2=pthread_create(&(tid[1]),NULL,&playandcount2,NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}

    //Main
    char cmd [100];
    while(1)
    {
        gets(cmd);
        //printf("%s", cmd);
        if(strcmp(cmd,"All Status")==0)
        {
            printf("Akmal WakeUp_Status = %d\n",ptrb->WakeUp_Status);
            printf("Siraj Spirit_Status = %d\n",ptra->Spirit_Status);

        }
        else if(strcmp(cmd,"Agmal Ayo Bangun")==0)
        {
            if(akmalloop ==3)
            {
                printf("Agmal Ayo Bangun sedang tidak dapat digunakan\n");
            }
            else
            {
                ptrb->WakeUp_Status+=15;
                if(sirajloop<3)sirajloop++;
               
            }
            
        }
        else if(strcmp(cmd,"Iraj Ayo Tidur")==0)
        {
            if(sirajloop ==3)
            {
                printf("Iraj ayo tidur sedang tidak dapat digunakan\n");
            }
            else
            {
                ptra->Spirit_Status-=20;
                if(akmalloop<3)akmalloop++;
            }
            
        }
        else
        {
            printf("perintah tidak dapat dimengerti\n");
        }

        if(a.Spirit_Status <= 0)
        {
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            break;
        }
         if(b.WakeUp_Status >= 100)
        {
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            break;
        }

    }



    return 0;
}
