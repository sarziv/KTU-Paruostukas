/* Failas: arvkap_aio02.c */
/*

    Kiek duomenø nuskaito source:posix|kespaul_aio01.c programa: ? (ar nuskaito uþsipraðytà 1MB)
    Sukurkite programà loginas_aio02.c (galite naudoti pavyzdþio ar savo anksèiau sukurtø programø fragmentus), kuri ið /dev/urandom su aio_read() nuskaitytø 1MB duomenø (t. y. tiek kiek praðoma).
        bus reikalingi pakartotiniai aio_read() iðkvietimai;
        reikës keisti adresà kur raðyti duomenis, kad neperraðytø ant jau nuskaitytø.

    Pabandykite originalià ir savo programas su /dev/random ir atsitiktiniø duomenø failu.

1MB atsitiktiniø duomenø failo kûrimas:

dd if=/dev/urandom of=atsitiktiniai_duomenys_1MB bs=1024 count=1024
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <aio.h>

#define BUFFLEN 1048576

int kp_test_open(const char *name);
int kp_test_close(int fd);
int kp_test_aio_read_start( const int d, struct aiocb *aiorp, void *buf, const int count );
int kp_test_dummy( const void *data, int n );
int kp_test_aio_read_waitcomplete( struct aiocb *aiorp );
int kp_test_open(const char *name){
   int dskr;
   dskr = open( name, O_RDONLY );
   if( dskr == -1 ){
      perror( name );
      exit(1);
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

int kp_test_aio_read_start( const int d, struct aiocb *aiorp, void *buf, const int count ){
   int rv = 0;
   memset( (void *)aiorp, 0, sizeof( struct aiocb ) );
   aiorp->aio_fildes = d;
   aiorp->aio_buf = buf;
   aiorp->aio_nbytes = count;
   aiorp->aio_offset = 0;
   rv = aio_read( aiorp );
   if( rv != 0 ){
      perror( "aio_read failed" );
      abort();
   }
   return rv;
}

int kp_test_dummy( const void *data, int n ){
   int i, cnt = 0;
   for( i = 0; i < n; i++ )
      if( ((char*)data)[i] == '\0' ) cnt++;
   printf( "Number of '0' in data: %d\n", cnt );
   return 1;
}

int kp_test_aio_read_waitcomplete( struct aiocb *aiorp ){
   const struct aiocb *aioptr[1];
   int rv;
   aioptr[0] = aiorp;
   rv = aio_suspend( aioptr, 1, NULL );
   if( rv != 0 ){
      perror( "aio_suspend failed" );
      abort();
   }
   rv = aio_return( aiorp );
   printf( "AIO complete, %d bytes read.\n", rv );
   return 1;
}

int main( int argc, char * argv[] ){
   int d;
   struct aiocb aior;
   char buffer[BUFFLEN];
   printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );
   d = kp_test_open( "/dev/urandom" );
   kp_test_aio_read_start( d, &aior, buffer, sizeof(buffer) );
   /*kp_test_aio_read_start( d, &aior, buffer, sizeof(buffer) );*/
   kp_test_aio_read_waitcomplete( &aior );
   kp_test_close( d );
   return 0;
}
