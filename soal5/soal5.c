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


int hunger = 200;
int hygiene =100;
int health = 300;
int *stok;
int cooldown = 20;
int input;
int status =0 ;
int enemy_health =100;
int my_stok = 10;
int m_attack;

pthread_t tid[7];//inisialisasi array untuk menampung thread dalam kasusu ini ada 2 thread

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

void* t_hunger(void*arg){
    while(1){
        while(status == 3){

        }
        pthread_t id = pthread_self();
        if (pthread_equal(id, tid[0]))
        {
            hunger = hunger -5;
            sleep(5);
        }
    }
}

void* t_hygiene(void *arg){
    while(1){
        while(status == 3){
            
        }
        pthread_t id =pthread_self();
        if (pthread_equal(id, tid[1]))
        {
            hygiene = hygiene -10;
            sleep(30);
            /* code */
        }
    }
}

void* t_health(void *arg){
    while(1){
        while(status == 3){
            
        }
        pthread_t id = pthread_self();
        if (pthread_equal(id, tid[2]))
        {
            health = health + 5;
            /* code */
            sleep(10);
        }
    }
}
void* standby(void *arg)
{
    while(1){
        if (status == 0) {
            pthread_t id=pthread_self();
            if(pthread_equal(id,tid[3]))//thread untuk menjalankan counter
            {
                input = getch();
                // printf("%d\n",input );
                if(input == 49){
                    if (my_stok > 0)
                    {
                        hunger = hunger + 15;
                        if (hunger > 200)
                        {
                            hunger = 200;
                            my_stok -- ;
                        }
                        else
                        {
                            my_stok -- ;    
                        }
                    }
                }
                else if(input == 50){
                    if (cooldown == 0)
                    {
                        hygiene = hygiene + 30;
                        cooldown = 20;
                    }
                    else{
                        printf("Gagal\n");
                    }
                }
                else if(input == 51){
                    status = 3;
                }
                else if(input == 52){
                    status =4;
                }
                else if (input == 53)
                {
                    status = -1;
                    /* code */
                }
            }
        }
    }
    return NULL;

}

void* battle(void *arg)
{
    while(1){
        if (status == 3) {
            pthread_t id=pthread_self();
            if(pthread_equal(id,tid[4]))//thread untuk menjalankan counter
            {
                if (enemy_health != 0 && health != 0){
                    input = getch();
                    if (input == 49)
                    {
                        if(m_attack == 1)
                        {
                            enemy_health = enemy_health - 20;
                            m_attack = 0;
                        }
                        else if(m_attack == 0 )
                        {
                            health = health - 20;
                            m_attack = 1;
                        }
                        status = 3;
                    }
                    else if(input == 50)
                    {
                        enemy_health =100;
                        status = 0;
                    }
                }
                else if (health == 0)
                {
                    status = -1;
                }
                if (enemy_health == 0)
                {
                    status = 0;
                    system("clear");
                    printf("Musuh kalah\n");
                    enemy_health = 100;
                }
                    
            }
        }
    }
}

void* shop_beli(void *arg)
{
    
    while(1){
        if (status == 4) {
            pthread_t id=pthread_self();
            if(pthread_equal(id,tid[5]))//thread untuk menjalankan counter
            {
                input = getch();
                if (input == 49)
                {
                    if(*stok>0){
                        my_stok ++;
                        (*stok) --;
                        status = 4;
                    }
                    else{
                        printf("Stok Habis\n");
                    }
                }
                else if(input == 50)
                {
                    status = 0;
                }
            }
        }
    } 
}



int main(void)
{
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);
    *stok = 20;
    pthread_create(&(tid[0]),NULL,t_hunger,NULL);//membuat thread
    pthread_create(&(tid[1]),NULL,t_hygiene,NULL);//membuat thread
    pthread_create(&(tid[2]),NULL,t_health,NULL);//membuat thread
    pthread_create(&(tid[3]),NULL,standby,NULL);//membuat thread
    pthread_create(&(tid[4]),NULL,battle,NULL);//membuat thread
    pthread_create(&(tid[5]),NULL,shop_beli,NULL);//membuat thread
    while(hunger>0&&hygiene>0&&health>0&&status!=-1){
        system("clear");
        if(status == 0){
            if (cooldown!= 0)
            {
            printf("Standby Mode\nHealth : %d\nHunger : %d\nHygiene : %d\nFood left : %d\nBath will be ready in %d\nChoices \n1.Eat \n2.Bath \n3.Battle \n4.Shop \n5.Exit \n", health, hunger, hygiene, my_stok, cooldown);
            }
            else
            {
            printf("Standby Mode\nHealth : %d\nHunger : %d\nHygiene : %d\nFood left : %d\nBath is ready \nChoices \n1.Eat \n2.Bath \n3.Battle \n4.Shop \n5.Exit \n", health, hunger, hygiene, my_stok);  
            }
        }
        if (status == 4)
        {
            printf("Shop Mode\nShop food stock : %d\nYour food stock : %d\nChoices \n1. Buy  \n2. Back \n", *stok, my_stok); 
        }
        if (status == 3)
        {
            /* code */
            printf("Battle Mode\nMonster’s Health : %d\nEnemy’s Health : %d\nchoices \n1. Attack  \n2. Run \n", health, enemy_health);
        }
        if(cooldown>0) cooldown--;
        sleep(1);
    }
    return 0;
}