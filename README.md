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

b. Urutkan input

	for(int i=1;i<argc-1;i++){
		for(int j=0;j<(argc-i-1);j++){
		if(strcmp(args[j+1],args[j+2])<0){
			temp=args[j+1];
			args[j+1]=args[j+2];
			args[j+2]=temp;
		}
		}
	}
      
c. Masukan input ke thread

      for(int i=0;i<argc-1;i++){
		  pthread_create(&(tid[i]),NULL,&hitung,(void*)args[i+1]);
	    }
      
d. Lakukan perhitungan faktorial

      void* hitung(void *args){
	    int b=strtol((char*)args,NULL,10);
	    int hasil=1;
	      if(b<0){
		    printf("ERROR!\n");
	      }
	      else{
	        for(int i=1;i<=b;i++){
		      hasil*=i;
	        }
	      printf("%d! = %d\n",b,hasil);
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

<b> Soal 3 </b>

#

<b> Soal 4 </b>

Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 

Jawaban :  [Script Soal 4](/soal4/soal4.c)

#

<b> Soal 5 </b>
