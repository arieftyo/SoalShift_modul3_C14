#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

int count=0;
int i,j,p,ans;

void *factorial(void *n){
	int index = *((int *)n);
	int x, factorial=1;
	for(x=1;x<=index;x++){
		factorial= factorial*x;
	}
	printf("%d!=%d\n",index, factorial);
}

int main(){
	pthread_t threads[300];
	int num[300];
	char a;
	int result[300];

	for(i=0;a!='\n';i++){
		scanf("%d%c", &num[i], &a);
		count++;
	}

	for(i=0;i<count;i++){
		for(j=i+1;j<count;j++){
			if(num[i]>num[j]){
				p=num[i];
				num[i]=num[j];
				num[j]=p;
			}		
		}
	}

	for(i=0;i<count;i++){
		result[i]=pthread_create(&(threads[i]), NULL, factorial, &num[i]);
		result[i]=pthread_join(threads[i],NULL);
	}
	
	return 0;
}
