# SoalShift_modul3_C14

## Nomor 1


Soal ini meminta kita untuk membuat program untuk menghitung bilangan faktorial secara paralel dan menampilkan hasilnya secara berurutan. Pada program ini, thread akan digunakan untuk menghitung faktorial pada tiap input (1 input menggunakan 1 thread). Input akan dimasukkan ke dalam array bernama num[300] lalu diurutkan. Lalu akan dilakukan looping thread sebanyak jumlah input dan isi dari looping tersebut adalah membuat thread yang memanggil fungsi function dengan parameter array num[i], lalu di joinkan sehingga hasilnya berurutan.

```
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
```


## Nomor 2

```
client 1 
    char * beli;
    scanf("%s", beli);
    send(sock , beli , strlen(beli) , 0 );
    valread = read(sock, buffer, 1024);
    printf("%s\n",buffer );
    
client 2

    char * tambah;
    scanf("%s", tambah);
    send(sock , tambah , strlen(tambah) , 0 );
    valread = read(sock, buffer, 1024);
    printf("%s\n",buffer );
```

Untuk client ada dibutuhkan varaibel sebagai pesan yang dikirim.

```
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
    		pthread_create(&(tid1), NULL, cekbeli, sambungan);
    		pthread_join(tid1,NULL);
	}
	else{
		char * gagal = "Sudah terkoneksi ";
		send(new_socket , gagal , strlen(gagal) , 0 );
		close(new_socket);
	}
 }
```

Untuk tiap server ditambahkan code seperti diatas untuk memastikan bahwa satu server hanya bisa terkoneksi satu client. Digunakan juga thread untuk menjalankan fungsi yang dimiliki server.


```
void* cekbeli(void *ptr){ 
    int a = *((int *) ptr);
    char *gagal = "Transaksi gagal";
    char *berhasil = "Transaksi berhasil";
    int valread;
    char buffer[1024] = {0};
    while(valread =  read( a , buffer, 1024)){
    	if(strcmp(buffer, "beli")==0){
    		if(*stok > 0){
		   (*stok)--;
           	   send(a, berhasil, strlen(berhasil), 0);
		}
		else{
	  		send(a , gagal , strlen(gagal) , 0 );
		}
		memset(buffer, 0, 1024);
    	}	
    }
    full = 0;
}
```

Server pembeli memiliki fungsi thread diatas. Fungsi tersebut bertujuan untuk mengecek input yang dimasukkan. Bila input  yang dimasukkan sama dengan beli maka stok akan berkurang dan menampilkan pesan transaki berhasil

```
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

```

Ada 2 thread yang dijalankan dalam server penjual. Yakni untuk melakukan transaki jual dan menampilkan stok setiap 5 detik. FUngsi hampir sama dengan server beli hanya saja stok berkurang.

## Nomor 3


Soal ini kami bikin dalam bentuk pilihan perintah. Jika memlih sebuah fitur maka thread 1,2, atau 3 akan dibuat sesuai dengan kondisi (if) yang ada di main. Thread tersebut akan memanggil fungsi function. Isi dari fungsi function adalah membandingkan id dari thread sekarang dengan thread kondisi if yang ada di main. Tujuan dari membandingkan id thread adalah jika id thread bersesuaian, maka thread tersebut akan menjalankan fungsinya sesuai dengan kondisi yang ada di dalam function tersebut.


```
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
```




## Nomor 4

```
if(pthread_equal(id,tid[0]))//thread untuk menjalankan counter
    {
        system("ps aux | head -10 > /home/ariefp/Documents/FolderProses1/SimpanProses1.txt");
    }
    else if(pthread_equal(id,tid[1]))
    {
        system("ps aux | head -10 > /home/ariefp/Documents/FolderProses2/SimpanProses2.txt");
    }
```
Langkah pertama adalah membuat thread untuk menyimpan list proses. Karena maks 10 maka digunakan head-10 untuk mengambil list 10 teratas. List kemudian disimpan dalam file SimpanProses1.txt dan yang kedua dalam file SimpanProses2.txt


```
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

```

Langkah kedua adalah mencompress file dalam zip. Perintah yang digunakan adalah zip -r. Namun sebelum itu digunakan mutex untuk memastikan bahwa thread untuk membuat file sudah selesai.


```
if(pthread_equal(id,tid[4]))//thread untuk menjalankan counter
    {
        system("unzip -j /home/ariefp/Documents/FolderProses1/KompresProses1.zip -d /home/ariefp/Documents/FolderProses1/");
    }
    else if(pthread_equal(id,tid[5]))
    {
        system("unzip -j /home/ariefp/Documents/FolderProses2/KompresProses2.zip -d /home/ariefp/Documents/FolderProses2/");
    }
```

Langkah selanjutnya menjalankan thread untuk mengekstrak file menggunakan perintah unzip -j /pathfile/ -d /pathtujuan/
Sama halnya dengan seblumnya digunakan mutex terlebih dahulu untuk memastikan bahwa thread ini berjalan setelah thread sebelumnya.


## Nomor 5

```
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
```
getch digunakan untuk menginput perintah tanpa harus menekan enter. Return berupa integer Asci dari inputan.

```
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
```

Ketiga thread diatas selalu berjalan untuk melaukan tugasnya masing masing. Berhenti berjalan jika masuk kedalam mode battle

```
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
                    hunger = hunger + 15;
                    my_stok -- ;
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

```

Thread untuk mode standby. Status digunakan untuk membedakan mode mode yang ada dalam permainan. Untuk mode standby memiliki status 0, battle statusnya 3, dan untuk shop statusnya 4. Untuk exit sendiri digunakan status = -1. Semua fungsi yang lain hampir sama, menyesuaikan pada fitur fitur yang ada dalam tiap mode.

Untuk stok digunakan shared memory karena nantinya stok dapat diakses dari thread penjual yang tidak termasuk satu file dalam file game.

```
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
```

Thread untuk battle

```
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
```
Thread untuk mode shop.

