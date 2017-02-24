/* Šarunas Živila KTU IFI-3 */
/* Failas: sarziv_nftw02.c */
/*
Sukurkite ir išbandykite programa loginas_nftw02.c, kuri su nftw() 
išvaikšciotu Jusu namu kataloga ir atspausdintu visu jame esanciu failu pavadinimus 
(t. y. pradetu paieška nuo Jusu namu katalogo ir naudotu FTW_PHYS, kad neišeitu iš jo radus simboline nuoroda).

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ftw.h>

int sz_test(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf);

int sz_test(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf){
	static int cnt = 0;
	puts(fpath);
	cnt++;
	return 0;
}

int main( int argc, char * argv[] ){
	int rv;
	int flags = 0;
	printf( "(C) Šarunas Živila, %s\n", __FILE__ );
	
	flags |= FTW_PHYS;
	rv = nftw(".", sz_test, 20, flags);
	
	if( rv == -1 ){
	  perror( "nftw failed" );
	  exit(1);
	}

	if( rv != 0 ){
	  printf( "ntfw fn %d != 0 -> nftw pabaiga\n", rv );
	}

	return 0;
}