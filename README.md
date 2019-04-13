# SoalShift_modul3_B09

<b> Soal 1 </b>

Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan

Jawaban :  [Script Soal 1](/soal1/soal1.c)

a. Parameter input dan inisialisasi thread

      	int main(int argc, char* args[]){
	pthread_t tid[argc-1]; //inisialisasi thread
      
Keterangan :

* argc : berfungsi untuk menghitung jumlah input
* args : berfungsi untuk menyimpan input

b. Ubah input ke array of integer lalu urutkan

	for(int i=0;i<argc-1;i++){
		konfersi[i]=atoi(args[i+1]);
	}

	for(int i=0;i<argc-2;i++){
		for(int j=0;j<(argc-i-2);j++){
		if(konfersi[j]<konfersi[j+1]){
			int temp=konfersi[j];
			konfersi[j]=konfersi[j+1];
			konfersi[j+1]=temp;
		}
		}
	}
      
c. Masukan input ke thread

      for(int i=0;i<argc-1;i++){
		pthread_create(&(tid[i]),NULL,&hitung,(void*)&konfersi[i]);
	}
      
d. Lakukan perhitungan faktorial

	void* hitung(void *args){
		int *b=(int *)args;
		int hasil=1;
		if(b<0){
			printf("ERROR!\n");
		}
		else{
			for(int i=1;i<=*b;i++){
			hasil*=i;
			}
		printf("%d! = %d\n",*b,hasil);
		}
	}

e. Jangan lupa menggunakan join

	    for(int i=0;i<argc-1;i++){
		  pthread_join(tid[i],NULL);
	    }

* Dengan menggunakan fungsi join, parent thread pada main function akan menunggu hingga child thread yang diinginkan selesai di eksekusi

f. Jalankan program

![Gambar](/Image/1.PNG)

#

<b> Soal 2 </b>

# 
1. Server Pembeli
Pada server pembeli buatlah socket yang melisten koneksi dari port 8081. Apabila sebuah koneksi telah diterima, lakukan close socket agar hanya ada 1 client yang terkoneksi.
apabila buffer yang diterima dari hasil read(socket) sama dengan beli, dan *value lebih besar dari 0, maka server akan mengirimkan "transaksi berhasil" ke client pembeli. Jika *value kurang dari sama dengan 0, maka server akan mengirimkan "transaksi gagal"

	while(1)
    	{
        	valread = read( new_socket , buffer, 1024);
        	if(strcmp(buffer,"beli")==0)
        	{
           		if((*value)>0)
            		{
                	(*value)--;
                	send(new_socket, berhasil, strlen(berhasil), 0);
            		}
            	else
            	{
                send(new_socket, gagal, strlen(berhasil), 0);
            	}    
        }
    }

2. Server Penjual
Pada server penjual, dibuat socket yang melisten dari port 8082. Apabila sebuah koneksi telah diterima, lakukan close socket agar hanya ada 1 client yang terkoneksi. Apabila buffer yang diterima dari read() berisi string "tambah", maka nilai *value (stok yang ada) akan bertambah 1.

	while(1)
    	{
        	valread = read( new_socket , buffer, 1024);
        	if(strcmp(buffer,"tambah")==0)
        	{
            	(*value) + = 1;
        }
    }

3. Client Beli
Pada client dibuat socket yang memint akoneksi ke port 8081. apabila array char reques berisi string "beli" maka client akan mengirimkan string "beli" ke server dan menunggu balasan. kemudian mengeread data yang dikirimkan server.

	while(1)
    	{
        	scanf("%s",reques);
        	if(strcmp(reques,"beli")==0)
        	{
            	send(sock , reques , strlen(reques) , 0 );
            	valread = read( sock , buffer, 1024); 
            	printf("%s\n",buffer ); 
        	}
        		else
        		{
            		printf("Request tidak dimengerti\n");
        		}
        sleep(1);
    }

4. Client Jual
Pada cliet jual, dibuatsocket yang meminta koneksi ke port 8082. apabila array char reques berisi string "tambah" maka client akan mengirimkan string "tambah" ke server.

	while(1)
    	{
        scanf("%s",reques);
        	if(strcmp(reques,"tambah")==0)
        	{
            	send(sock , reques , strlen(reques) , 0 );
        	}
        	else
        	{
            	printf("Request tidak dimengerti\n");
        	}
        sleep(1);
    	}

<b> Soal 3 </b>

Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
Terdapat 2 karakter Agmal dan Iraj
Kedua karakter memiliki status yang unik
Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
Iraj memiliki Spirit_Status, di awal program memiliki status 100
Terdapat 3 Fitur utama
All Status, yaitu menampilkan status kedua sahabat
Ex: Agmal WakeUp_Status = 75 
      Iraj Spirit_Status = 30
“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
Terdapat Kasus yang unik dimana:
Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
Program akan berhenti jika Salah Satu :
WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)


Syarat Menggunakan Lebih dari 1 Thread

1. Buatlah 2 thread, thread pertama 
```
	void* playandcount1(void *arg)
	{
		while(1)
		{
			if(*sl ==3)
			{
				printf("Siraj ayo tidur tidak dapat digunakan dalam 10 detik\n");
				sleep(10);
				*sl = 0;
			}
		}
		return NULL;
	}
```

berguna untuk mencegah fitur "Siraj ayo tidur" dijalankan selama 10 detik.

* thread kedua
```
	void* playandcount2(void *arg)
	{
		while(1)
		{
			if(*al ==3)
			{
				printf("Aqmal ayo bangun tidak dapat digunakan dalam 10 detik\n");
				sleep(10);
				*al = 0;
			}
		}
		return NULL;
	}
```

* Pada fungsi main, ketika pengguna mengetikkan "All Status" maka akan menampilkan semua status yang ada. setiap kali pengguna menggunakan fitur Agmal ayo bangun atau Iraj ayo tidur, counter dari masing2 fitur akan diincrement. apabila telah mencapai 3, maka kondisi dari thread akan dijalankan (menyebabkan fitur disleep). apabila waktu telah dipenuhi, maka counter akan direset.

* Apabila salah satu status telah mencapai kondisi tertentu, maka program akan keluar.
`````
	if(a.Spirit_Status <= 0)
        {
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            break;
        }
         if(b.WakeUp_Status >= 100)
        {
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            break;
        }
`````

<b> Soal 4 </b>

Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 

Jawaban :  [Script Soal 4](/soal4/soal4.c)

a. Mengambil 10 list proses yang sedang berjalan lalu menyimpannya di SimpanProsesX.txt (X=1,2)

	char ambil[1000]="ps -aux | head -%d | tail -%d > /home/karinasraya/Documents/FolderProses%d/SimpanProses%d.txt";
	strcpy(ekse,"");
	sprintf(ekse,ambil,extract->max,10,extract->pros,extract->pros);
	system(ekse);
	
b. Mengkompres zip file

	char zip[1000]="zip -qmj /home/karinasraya/Documents/FolderProses%d/KompresProses%d 
	/home/karinasraya/Documents/FolderProses%d/SimpanProses%d.txt";
	strcpy(ekse,"");
	sprintf(ekse,zip,extract->pros,extract->pros,extract->pros,extract->pros);
	system(ekse);
	
c. Tunggu 15 detik

	sleep(15);
	
d. Mengekstrak kembali file

	char unzip[1000]="unzip -qd /home/karinasraya/Documents/FolderProses%d 
	/home/karinasraya/Documents/FolderProses%d/KompresProses%d.zip";

	strcpy(ekse,"");
	sprintf(ekse,unzip, extract->pros, extract->pros, extract->pros);
	system(ekse);

e. Jalankan program

![Gambar](/Image/4a.PNG)
![Gambar](/Image/4b.PNG)
![Gambar](/Image/4c.PNG)

#

<b> Soal 5 </b>

* ada beberapa thread
````
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
````

* thread hungry berguna untuk mengurangi stat hunger per waktu tertentu
* thread bau berguna untuk mengurangi stat hygen perwaktu tertentu
* thread regen berguna untuk menambah stat health perwarktu tertentu
* thread makanchecker dan mandichecker berguna  untuk mengecheck apakah monster boleh makan/ mandi(stok makanan ada dan mandi sedang tidak cooldown)

* kemudian ada beberapa fungsi
`````
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

`````
* void siaga,batul,toko berguna untuk memilih schene game yang diinginkan. void makan untuk menambah stat makan dan mengurangi stock makanan, void mandi untuk menambah stat hygen dan membuat fitur tersebut cooldown untuk beberapa waktu, void pilihscene untuk memudahkan memilih scene yang diinginkan.
dan char getch() berguna sebagai input handler dari game.

````
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

````
* Variabel enemyhp berguna sebagai indikator dari nyawa musuh. variabel dengan tipedata monster berguna untuk menyimpan data2 monster. variabel jam berguna untuk menyimpan data waktu terakhir dari makan dan mandi. mandiyuk dan makanyuk berguna sebagai indikator apakah monster boleh makan atau mandi.

* Game dimmulai dengan beberapa stat dari monster telah diinputkan. ketika pemain menekan suatu angka, fungsi getch secara otomatis akan mengambilnya sebagai input dan memilih kondisi if else yang bersesuaian dengan input dan schene saat ini. apabila nyawa monster kita mencapai 0 maka program akan keluar. begitu pula jika stat hunger dan hygen mencapai 0.

* Untuk program penjual
````
	ey_t key = 1234;
int *gudang;

char getch(){
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
    return buf;
 }

 int main()
 {
     int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        gudang = shmat(shmid, NULL, 0);
        *gudang=0;

    char cmd;
    while(1)
    {
        system("clear");
        printf("scene Toko versi Penjual\n");
        printf("Stock Toko:%d\n",*gudang);
        printf("Masukkan pilihan\n");
    printf("1.Restock\n2.Back\n");
        cmd=getch();
        if(cmd=='1')
        {
            *gudang = *gudang + 1;
        }
        else
        {
            break;
        }
        
    }
````

* Juga menggunakan fitur getch, ketika cmd mengandung char 1 maka stok di gudang akan diincrement sebanyak 1. Antara game dan program penjual, menggunakan shared memmory.
