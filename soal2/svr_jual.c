// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PORT 8082

pthread_t tid[1];
int *value;

void* playandcount(void *arg)
{
    int num;
    while(1)
    {
        num = *value;
        printf("stok sekarang: %d\n",num);
        sleep(5);
    }
    
    return NULL;
}

int main(int argc, char const *argv[]) 
{ 
        key_t key = 1234;
        

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        value = shmat(shmid, NULL, 0);
        
        *value = 5;
    
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 

    address.sin_port = htons(PORT);
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 0) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    close(server_fd);

    printf("Server dimulai\n");

    //Membuat thread
    int err=pthread_create(&(tid[1]),NULL,&playandcount,NULL);
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			//printf("\n create thread success\n");
		}

    //Proccessing Request
    //int stok = 5;
    char berhasil[] = "Transaksi berhasil";
    char gagal[] = "Transaksi gagal";

    while(1)
    {
        valread = read( new_socket , buffer, 1024);
        if(strcmp(buffer,"tambah")==0)
        {
            (*value) + = 1;
            //printf("stok sekarang: %d\n",stok);  
        }
        //sleep(1); 
    }

    // valread = read( new_socket , buffer, 1024);
    // printf("valread: %d\n",valread); 
    // printf("%s\n",buffer ); 
    // send(new_socket , hello , strlen(hello) , 0 ); 
    // printf("Hello message sent\n"); 

    return 0; 
} 
