/* Failas: arvkap_nftw02.c */
/*

    Sukurkite ir iðbandykite programà loginas_nftw02.c, kuri su nftw() iðvaikðèiotø Jûsø namø katalogà ir atspausdintø visø jame esanèiø failø pavadinimus (t. y. pradëtø paieðkà nuo Jûsø namø katalogo ir naudotø FTW_PHYS, kad neiðeitø ið jo radus simbolinæ nuorodà).
    Ákelkite programos tekstà á Moodle.

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