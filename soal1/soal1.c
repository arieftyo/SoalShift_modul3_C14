#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

int count=0;
int i,j,p,ans;
int fak[300];
int urutan[300];
int b= 0;

void *factorial(void *n){
	int index = *((int *)n);
	int x, factorial=1;
	int self_id;
	self_id=pthread_self();
	printf("Thread %u \n",self_id);
	
	for(x=1;x<=index;x++){
		factorial= factorial*x;
	}
	urutan[b] = index;
	fak[b] = factorial;
	b++;
}

int main(int argc, char *argv[]){
	pthread_t threads[300];
	char a;
	int result[300];
	int num[300];

	for(i=0;a!='\n';i++){
		scanf("%d%c", &num[i], &a);
		count++;
	}

	
	for(i=0;i<count;i++){
		result[i]=pthread_create(&(threads[i]), NULL, factorial, &num[i]);
	}
	
	for(i=0;i<count;i++){
		result[i]=pthread_join(threads[i],NULL);
	}

	for(i=0;i<count;i++){
		for(j=i+1;j<count;j++){
			if(fak[i]>fak[j]){
				p=fak[i];
				fak[i]=fak[j];
				fak[j]=p;
				
				p = urutan[i];
				urutan[i] = urutan[j];
				urutan[j] = p;
			}		
		}
	}
	for(i=0;i<count;i++){
		printf("%d!=%d\n",urutan[i], fak[i]);
	}
	
	return 0;
}