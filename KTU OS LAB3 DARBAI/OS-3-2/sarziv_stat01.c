/* Šarunas Živila KTU IFI-3 */
/* Failas: arvkap_stat01.c */
/*
ukurkite programa loginas_stat01.c (loginas pakeiskite i savo logina), kuri su stat() ar fstat() gautu informacija apie komandines elutes parametru jai nurodyta faila, kataloga ar kt. ir išvestu i ekrana stat strukturos turini:
savininko ID
dydi
i-node numeri
leidimus
failo tipa (katalogas/failas/konvejeris/soketas...)
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int sz_test();

int sz_test(){
   return 0;
}

int main( int argc, char * argv[] ){
	struct stat *num = malloc(sizeof(struct stat));
	
	printf( "(C) Šarunas Živila, %s\n", __FILE__ );
	
	if(argc != 2){ // arg turi buti 2
		printf("Naudojimas:\n %s failas_ar_katalogas\n", argv[0]);
		system ("pause");
	}
	
	stat(argv[1], buf);
	
	printf("Failas ar katalogas: '%s'\n", argv[1]);
	printf("Savininko ID: %d\n", num->st_uid);
	printf("Dydis: %ld\n", num->st_size);
	printf("i-nr: %ld\n", num->st_ino);
    printf("Failo priejimas: \t");
    printf((S_ISDIR(buf->st_mode)) ? "d" : "-");
    printf((num->st_mode & S_IRUSR) ? "r" : "-");
    printf((num->st_mode & S_IWUSR) ? "w" : "-");
    printf((num->st_mode & S_IXUSR) ? "x" : "-");
    printf((num->st_mode & S_IRGRP) ? "r" : "-");
    printf((num->st_mode & S_IWGRP) ? "w" : "-");
    printf((num->st_mode & S_IXGRP) ? "x" : "-");
    printf((num->st_mode & S_IROTH) ? "r" : "-");
    printf((num->st_mode & S_IWOTH) ? "w" : "-");
    printf((num->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");	
	free(num);
	
	return 0;
}