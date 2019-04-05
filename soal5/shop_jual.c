#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
#include <termios.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>

pthread_t tid[7];//inisialisasi array untuk menampung thread dalam kasusu ini ada 2 thread
int *stok;
int status;
int input;


int getch(void) {
      int c=0;

      struct termios org_opts, new_opts;
      int res=0;
          //-----  store old settings -----------
      res=tcgetattr(STDIN_FILENO, &org_opts);
      assert(res==0);
          //---- set new terminal parms --------
      memcpy(&new_opts, &org_opts, sizeof(new_opts));
      new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
      tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
      c=getchar();
          //------  restore old settings ---------
      res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
      assert(res==0);
      return(c);
}

void* shop_jual(void *arg)
{
    
    while(1){
        if (status == 0) {
            pthread_t id=pthread_self();
            if(pthread_equal(id,tid[0]))//thread untuk menjalankan counter
            {
                input = getch();
                if (input == 49)
                {
                    if(*stok>0){
                        (*stok) ++;
                        status = 0;
                    }
                    else{
                        printf("Stok Habis\n");
                    }
                }
                else if(input == 50)
                {
                    status = -1;
                }
            }
        }
    } 
}

int main(int argc, char const *argv[])
{
	key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
   	stok = shmat(shmid, NULL, 0);
    pthread_create(&(tid[0]),NULL,shop_jual,NULL);//membuat thread
    while(*stok>0&&status!=-1){
    	system("clear");
    	if (status == 0)
    	{
    		printf("Shop\nFood stock : %d\nChoices\n1.Restock\n2.Exit\n", *stok);
    	}
    	sleep(1);
    }

	return 0;
}
