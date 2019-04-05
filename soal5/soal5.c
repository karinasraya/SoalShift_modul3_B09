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

char scene='1';
char* sceneptr=&scene;
int makanyuk=1;
int mandiyuk=1;
int *makanptr=&makanyuk;
int *mandiptr=&mandiyuk;

int stokmakan=2;
int *stokmakanptr=&stokmakan;

int battleturn=0;
int *battleptr=&battleturn;
int enemyhp=100;
int* enemyptr=&enemyhp;

pthread_t tid[10];

typedef struct 
{
    time_t lst_eat;
    time_t lst_bath;
}timestat;

timestat myMonster;
timestat *jam = &myMonster;


typedef struct 
{
    char name[100];
    int hunger_stat;
    int hygen_stat;
    int health;
}monster;

monster deku;
monster *dekuptr = &deku;

void siaga(char* sceneptr, int cmd)
{
    system("clear");
    printf("Scene Siaga\n");
    printf("%s\n",dekuptr->name);
    printf("Health :%d\n",dekuptr->health);
    printf("Hunger :%d\n", dekuptr->hunger_stat);
    printf("Hygene :%d\n", dekuptr->hygen_stat);
    printf("Stok makanan: %d\n", *stokmakanptr);
    if(*mandiptr==1)printf("Siap untuk mandi\n");
    else
    {
        printf("mandi akan siap dalam %f detik\n",20.0 - difftime(time(NULL),jam->lst_bath));
    }
    
    printf("Select Choice\n");
    printf("1.Eat\n2.Bath\n3.Battle\n4.Shop\n5.Exit\n");

}

void* hungry(void *arg)
{
	while(1)
    {
        if(*sceneptr=='1')
        {
            sleep(10);
            dekuptr->hunger_stat-=5;
        }
    }
	return NULL;
}

void* bau(void *arg)
{
	while(1)
    {
        if(*sceneptr=='1')
        {
            sleep(30);
            dekuptr->hygen_stat= dekuptr->hygen_stat - 10;
        }
        
    }
	return NULL;
}

void* regen(void *arg)
{
	while(1)
    {
        if(*sceneptr=='1')
        {
            sleep(10);
            dekuptr->health+=5;
        }
        
    }
	return NULL;
}

void* mandichecker(void *arg)
{
	while(1)
    {
        while(*mandiptr==0)
        {
            if(difftime(time(NULL),jam->lst_bath) >20)
            {
                *mandiptr=1;
            }
        }
    }
	return NULL;
}

void* makanchecker(void *arg)
{
    while(1)
    {
	    while(*stokmakanptr<=0)
        {
            if(*stokmakanptr>0)
            {
                *makanptr=1;
            }
            
        
        }
    }
	return NULL;
}

void makan()
{
    dekuptr->hunger_stat+=15;
    if(dekuptr->hunger_stat>200)
    {
        dekuptr->hunger_stat = 200;
    }
    jam->lst_eat = time(NULL);
    if(*stokmakanptr>0)
    {
        (*stokmakanptr)= *stokmakanptr-1;
        if(*stokmakanptr<=0)
        {
         (*makanptr)=0;
        }
    }
}

void mandi()
{
    dekuptr->hygen_stat+=30;
    jam->lst_bath = time(NULL);
    *mandiptr=0;
}


void batul(char* sceneptr, int cmd)
{
    if(*battleptr==0)
    {
        *enemyptr=100;
        *battleptr=1;
    }
    system("clear");
    printf("Scene Battle\n");
    printf("Your health :%d\n",dekuptr->health);
    printf("Enemy health :%d\n",*enemyptr);
    printf("Select Choice\n");
    printf("1.Attack\n2.Run\n");

}

void toko(char* sceneptr, int cmd)
{
    system("clear");
    printf("scene Toko\n");
    printf("Your Stock %d\n",*stokmakanptr);
    printf("Store stock :%d\n",*gudang);
    printf("Select Choice\n");
    printf("1.Beli\n2.Back\n");
}

void pilihscene(char cmd)
{
    printf("%c\n",cmd);
    if(cmd == '1')siaga(sceneptr,1);
    else if(cmd=='2')batul(sceneptr,2);
    else if(cmd=='3')toko(sceneptr,3);
}

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


int main()
{
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        gudang = shmat(shmid, NULL, 0);
   
    dekuptr->hunger_stat=200;
    dekuptr->hygen_stat=100;
    dekuptr->health=300;

    printf("Masukkan nama monster!\n");
    gets(dekuptr->name);


    //char untuk command
    char cmd;
    int err;

        err=pthread_create(&(tid[0]),NULL,&hungry,NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}

        err=pthread_create(&(tid[0]),NULL,&bau,NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
        err=pthread_create(&(tid[0]),NULL,&regen,NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
        err=pthread_create(&(tid[0]),NULL,&mandichecker,NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
        // err=pthread_create(&(tid[0]),NULL,&makanchecker,NULL); //membuat thread
		// if(err!=0) //cek error
		// {
		// 	printf("\n can't create thread : [%s]",strerror(err));
		// }
		// else
		// {
		// 	printf("\n create thread success\n");
		// }
   
    system("clear");
    pilihscene('1');
    while(1)
    {
        if(dekuptr->hunger_stat <=0 || dekuptr->hygen_stat<=0 || dekuptr->health <=0)
        {
            system("clear");
            printf("Game Over\n");
            sleep(1);
            break;
        }
        //printf("masukkan perintah\n");
        cmd=getch();
        if(*sceneptr=='1' && cmd=='1')
        {
            //if((*stokmakanptr)>0)
            if((*makanptr)>0)
            {
                makan();
                pilihscene('1');
            }
            else
            {
                pilihscene('1');
            }
            
        }
        else if(*sceneptr=='1' && cmd=='2')
        {
            if(*mandiptr==1)
            {
                mandi();
                pilihscene('1');
            }
            else
            {
                pilihscene('1');
            }
        }
        else if(*sceneptr=='1' && cmd=='3')
        {
            *sceneptr='2';
            pilihscene('2');
        }
        else if(*sceneptr=='1' && cmd=='4')
        {
            *sceneptr='3';
            pilihscene('3');
        }
        else if(*sceneptr=='1' && cmd=='5')
        {
            break;
        }
        else if(*sceneptr=='2' && cmd=='1')
        {
            dekuptr->health-=20;
            (*enemyptr) = (*enemyptr) - 20;
            if(dekuptr->health==0)
            {
                system("clear");
                printf("Gameover\n");
                sleep(1);
                break;
            }
            else if(*enemyptr ==0)
            {
                system("clear");
                printf("Anda menang!\n");
                *battleptr = 0;
                sleep(1);
                *sceneptr='1';
                pilihscene('1');
            }
            else
            {
                pilihscene('2');
            }
            
            
        }
        else if(*sceneptr=='2' && cmd=='2')
        {
            system("clear");
            printf("Anda Pecundang!\n");
            *battleptr = 0;
            sleep(1);
            *sceneptr='1';
            pilihscene('1');
        }
        else if(*sceneptr=='3' && cmd=='1')
        {
            if(*gudang>0)
            {
                *stokmakanptr = *stokmakanptr + 1;
                *gudang = *gudang - 1;
            }
            pilihscene('3');
        }
        else if(*sceneptr=='3' && cmd=='2')
        {
            *sceneptr='1';
            pilihscene('1');
        }
        

    }
    shmdt(gudang);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}