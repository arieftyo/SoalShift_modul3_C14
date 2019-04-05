#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 8080
#include <sys/ipc.h>
#include <sys/shm.h>

void *cektambah(void *ptr);
void* cetakstok();

int *stok;
int full= 0; 

int main(int argc, char const *argv[]) {
    pthread_t tid1, tid2;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 10;  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    /*if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }*/


    /*int *sambungan = malloc(sizeof(*sambungan));
    *sambungan = new_socket;
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    pthread_create(&(tid1), NULL, cekbeli, sambungan);
    pthread_join(tid1,NULL);*/
    while(1){
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    	if(!full){
    		int *sambungan = malloc(sizeof(*sambungan));
        		*sambungan = new_socket;
        		valread = read( new_socket , buffer, 1024); 
        		printf("%s\n",buffer );
        		send(new_socket , hello , strlen(hello) , 0 );
    		full = 1;    		
    		printf("Hello message sent\n");
    		pthread_create(&(tid2), NULL, cetakstok, sambungan);
        	pthread_create(&(tid1), NULL, cektambah, sambungan);
        	pthread_join(tid1,NULL);
    	}
    	else{
    		char * gagal = "Sudah terkoneksi ";
    		send(new_socket , gagal , strlen(gagal) , 0 );
    		close(new_socket);
    	}
    }
    return 0;
}

void* cektambah(void *ptr){ 
    int a = *((int *) ptr);
    char *gagal = "Transaksi gagal";
    char *berhasil = "Transaksi berhasil";
    int valread;
    char buffer[1024] = {0};
    while(valread =  read( a , buffer, 1024)){
    	if(strcmp(buffer, "tambah")==0){
   		   (*stok)++;        	
    	}	
    }
    full = 0;
}

void* cetakstok(){
    while(1){
	printf("Stok : %d\n", *stok);
	sleep(5);
    }
}

