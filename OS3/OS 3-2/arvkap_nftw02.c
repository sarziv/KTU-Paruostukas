/* Failas: arvkap_nftw02.c */
/*

    Sukurkite ir i�bandykite program� loginas_nftw02.c, kuri su nftw() i�vaik��iot� J�s� nam� katalog� ir atspausdint� vis� jame esan�i� fail� pavadinimus (t. y. prad�t� paie�k� nuo J�s� nam� katalogo ir naudot� FTW_PHYS, kad nei�eit� i� jo radus simbolin� nuorod�).
    �kelkite programos tekst� � Moodle.

    PASTABA: dirbant su failais taip pat gali praversti fnmatch() funkcija.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ftw.h>

int vp_test(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf);

int vp_test(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf){
	static int cnt = 0;
	puts(fpath);
	cnt++;
	return 0;
}

int main( int argc, char * argv[] ){
	int rv;
	int flags = 0;
	printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );
	
	flags |= FTW_PHYS;
	rv = nftw(".", vp_test, 20, flags);
	
	if( rv == -1 ){
	  perror( "nftw failed" );
	  exit( 1 );
	}

	if( rv != 0 ){
	  printf( "ntfw fn function returnd %d != 0 -> nftw finished\n", rv );
	}

	return 0;
}