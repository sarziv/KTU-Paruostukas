/* Failas: arvkap_mmap02.c */
/*

    Sukurkite programa loginas_mmap02.c, kuri nukopijuotø failus naudojant mmap() (kad bûtø paprasèiau laikykime, kad failø dydþiai iki 100MB, t. y. abu telpa á 32bit proceso erdvæ):
        atidarytø ir prijungtø 2 programos argumentais nurodytus failus su mmap() (vienà ið jø tik skaitymui, tik skaitomo failo dydá galite suþinoti su fstat() funkcija)
        nukopijuotø vieno failo turiná á kità (su memcpy() ar paprastu ciklu)
        atjungtø abu failus
        uþdarytø abu deskriptorius

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>

#define SIZE 1048576

int kp_test_openw(const char *name);
int kp_test_close(int fd);
void* kp_test_mmapw( int d, int size );
int kp_test_munamp( void *a, int size );
int kp_test_usemaped( void *a, int size );
char *ps_map(int d, int size, int read);

int kp_test_openw(const char *name){
   int dskr;
   dskr = open( name, O_RDWR | O_CREAT | O_EXCL, 0640 );
   if( dskr == -1 ){
      perror( name );
      exit( 255 );
   }
   printf( "dskr = %d\n", dskr );
   return dskr;
}

int kp_test_close(int fd){
   int rv;
   rv = close( fd );
   if( rv != 0 ) perror ( "close() failed" );
   else puts( "closed" );
   return rv;
}

void* kp_test_mmapw( int d, int size ){
   void *a = NULL;
   lseek( d, size - 1, SEEK_SET );
   write( d, &d , 1 );        /* iraso bile ka i failo gala */
   a = mmap( NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, d, 0 );
   if( a == MAP_FAILED ){
      perror( "mmap failed" );
      abort();
   }
   return a;
}

int kp_test_munamp( void *a, int size ){
   int rv;
   rv = munmap( a, size );
   if( rv != 0 ){
      puts( "munmap failed" );
      abort();
   }
   return 1;
}

int kp_test_usemaped( void *a, int size ){
   memset( a, 0xF0, size );
   return 1;
}


char *ps_map(int d, int size, int read){
	void *buf;
	if(!read){
		lseek(d, size - 1, SEEK_SET);
		write(d, &d, 1);
		buf = mmap(NULL, size, PROT_WRITE|PROT_READ, MAP_SHARED, d, 0);
	}else{
		buf = mmap(NULL, size, PROT_READ, MAP_SHARED, d, 0);
	}
	if( buf == MAP_FAILED ){
	  perror( "mmap failed" );
	  abort();
	}
	return buf;
}

int main( int argc, char * argv[] ){

	int rd, wd, s;
	struct stat status;
	void *rm, *wm;

	printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );
	if(argc < 3){
		printf("Reikia 2 argumentu: skaitymui ir rasymui\n");
		exit(255);
	}   
	
	if( (rd = open(argv[1], O_RDONLY) ) == -1){
		perror("ps_test_open pirmam failui klaida");
		return -1;
	}	

	if( (wd = open(argv[2], O_RDWR|O_CREAT, S_IRWXU|S_IWGRP|S_IROTH) ) == -1){
		perror("ps_test_open antram failui klaida");
		return -1;
	}
	
	s = status.st_size;
	printf("Dydis - %d baitu\n", s);
	rm = ps_map(rd, s, 1);
	wm = ps_map(wd, s, 0);	
	memcpy(wm, rm, s);
	
	close(rd);
	close(wd);
	
	return 0;
}