/* Failas: arvkap_stat01.c */
/*
Funkcijos stat() ir fstat() skirtos suþinoti informacijai apie failø sistemos objektus (failus, katalogus, spec. failus, ir t.t.).

    Sukurkite programà loginas_stat01.c (loginas pakeiskite á savo loginà), kuri su stat() ar fstat() gautø informacijà apie komandinës elutës parametru jai nurodytà failà, katalogà ar kt. ir iðvestø á ekranà stat struktûros turiná:
        savininko ID
        dydá
        i-node numerá
        leidimus
        failo tipà (katalogas/failas/konvejeris/soketas...)
    Palyginkite savo programos ir stat komandos gràþinamus rezultatus ávairiems failams. Turëtumëte matyti tà paèià informacijà (nebûtinai vienodai atvaizduotà).

*/

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int vp_test();

int vp_test(){
   return 0;
}

int main( int argc, char * argv[] ){
	struct stat *buf = malloc(sizeof(struct stat));
	
	printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );
	
	if(argc != 2){ /*Ar yra nurodyta reiksme*/
		printf("Naudojimas:\n %s failas_ar_katalogas\n", argv[0]);
		exit(255);
	}
	
	stat(argv[1], buf);
	
	printf("Failas ar katalogas: '%s'\n", argv[1]);
	printf("Savininko ID: %d\n", buf->st_uid);
	printf("Dydis (baitais): %ld\n", buf->st_size);
	printf("i-node: %ld\n", buf->st_ino);
    printf("Failo teises: \t");
    printf((S_ISDIR(buf->st_mode)) ? "d" : "-");
    printf((buf->st_mode & S_IRUSR) ? "r" : "-");
    printf((buf->st_mode & S_IWUSR) ? "w" : "-");
    printf((buf->st_mode & S_IXUSR) ? "x" : "-");
    printf((buf->st_mode & S_IRGRP) ? "r" : "-");
    printf((buf->st_mode & S_IWGRP) ? "w" : "-");
    printf((buf->st_mode & S_IXGRP) ? "x" : "-");
    printf((buf->st_mode & S_IROTH) ? "r" : "-");
    printf((buf->st_mode & S_IWOTH) ? "w" : "-");
    printf((buf->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");	
	printf("Failo tipas: %s\n", (S_ISREG(buf->st_mode)) ? "paprastas failas" : "katalogas");
	
	free(buf);
	
	return 0;
}

/*
PVZ: 
argv[0] - a.out
argv[1] - reiksme (pvz) 'a.out reiksme'
*/