#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>


int WakeUp_Status = 0;
int Spirit_Status = 100;
int num;
int count1;
int count2;
pthread_t thread[3];

void *function(){
	pthread_t id=pthread_self();
	if(pthread_equal(id,thread[0])){
		printf("Agmal WakeUp_Status = %d \nIraj Spirit_Status = %d\n\n", WakeUp_Status, Spirit_Status);
	}
	else if(pthread_equal(id,thread[1])){
		WakeUp_Status+=15;
		count1++;
		if(count1 == 3){
			printf("Fitur Iraj Ayo Tidur Disabled 10s\n\n");
			sleep(10);
			count1=0;		
		}
	}
	else if(pthread_equal(id,thread[2])){
		Spirit_Status-=20;
		count2++;
		if(count2 == 3){
			printf("Fitur Agmal Ayo Bangun Disabled 10\n\n");
			sleep(10);
			count2=0;
		}
	}
}

int main(){
	int ftr;
	printf("Pilih fitur: \n1.All Status \n2.Agmal Ayo Bangun \n3.Iraj Ayo Tidur \n");
	
	while(1){
		scanf("%d", &num);
		function(num);
		if(WakeUp_Status >= 100){
			printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
			break;
		}
		else if(Spirit_Status <= 0){
			printf("Iraj ikut tidur dan bangun kesiangan bersama Agmal\n");
			break;
		}


		if(num == 1){
			ftr=pthread_create(&(thread[0]),NULL,&function,NULL);
		}
		else if(num == 2){
			ftr=pthread_create(&(thread[1]),NULL,&function,NULL);
		}
		else if(num == 3){
			ftr=pthread_create(&(thread[2]),NULL,&function,NULL);
		}
	}
}
