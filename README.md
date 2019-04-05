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

#

<b> Soal 2 </b>

#

<b> Soal 3 </b>

#

<b> Soal 4 </b>

#

<b> Soal 5 </b>
