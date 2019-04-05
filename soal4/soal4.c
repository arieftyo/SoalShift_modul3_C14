#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
 
pthread_t tid[6];
int status;
int nomor;
 
void* buatfile(void *arg)
{
    status =0;
    unsigned long i=0;
    pthread_t id=pthread_self();
    if(pthread_equal(id,tid[0]))//thread untuk menjalankan counter
    {
        system("ps aux | head -10 > /home/ariefp/Documents/FolderProses1/SimpanProses1.txt");
    }
    else if(pthread_equal(id,tid[1]))
    {
        system("ps aux | head -10 > /home/ariefp/Documents/FolderProses2/SimpanProses2.txt");
    }
    status =1;
    return NULL;
}

void* compress(void *arg)
{
    while(status != 1)
    {

    }
    pthread_t id=pthread_self();
    if(pthread_equal(id,tid[2]))//thread untuk menjalankan counter
    {
        system("zip -r /home/ariefp/Documents/FolderProses1/KompresProses1.zip /home/ariefp/Documents/FolderProses1/SimpanProses1.txt");
        system("rm /home/ariefp/Documents/FolderProses1/SimpanProses1.txt");
    }
    else if(pthread_equal(id,tid[3]))
    {
        system("zip -r /home/ariefp/Documents/FolderProses2/KompresProses2.zip /home/ariefp/Documents/FolderProses2/SimpanProses2.txt");
        system("rm /home/ariefp/Documents/FolderProses2/SimpanProses2.txt");
    }

    status =2;
    return NULL;

}

void* extract(void *arg)
{
    while(status !=2)
    {

    }
    sleep(15);
    
    pthread_t id=pthread_self();
    if(pthread_equal(id,tid[4]))//thread untuk menjalankan counter
    {
        system("unzip -j /home/ariefp/Documents/FolderProses1/KompresProses1.zip -d /home/ariefp/Documents/FolderProses1/");
    }
    else if(pthread_equal(id,tid[5]))
    {
        system("unzip -j /home/ariefp/Documents/FolderProses2/KompresProses2.zip -d /home/ariefp/Documents/FolderProses2/");
    }
    status =3;
    return NULL;
}

int main(void)
{
    unsigned long i=0;
    unsigned long j=0;
    int err;
    int err2;
    while(i<2)//looping membuat thread 2x
    {
        err=pthread_create(&(tid[i]),NULL,&buatfile,NULL);//membuat thread
        if(err!=0)//cek error
        {
            printf("can't create thread : [%s]\n",strerror(err));
        }
        else
        {
            printf("create file success\n");
        }
        i++;
    }

    while(i<4)//looping membuat thread 2x
    {
        err=pthread_create(&(tid[i]),NULL,&compress,NULL);//membuat thread
        if(err!=0)//cek error
        {
            printf("can't create thread : [%s]\n",strerror(err));
        }
        else
        {
            printf("create file success\n");
        }
        i++;
    }

    while(i<6)//looping membuat thread 2x
    {
        err=pthread_create(&(tid[i]),NULL,&extract,NULL);//membuat thread
        if(err!=0)//cek error
        {
            printf("can't create thread : [%s]\n",strerror(err));
        }
        else
        {
            printf("create file success\n");
        }
        i++;
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    pthread_join(tid[4],NULL);
    pthread_join(tid[5],NULL);
    
    return 0;
}