/* Failas: arvkap_rw01.c */
/*
Sukurkite program� loginas_rw01.c, kuri:

    atidaryt� komandin�je eilut�je nurodyt� fail� tik skaitymui su open();
    atidaryt� kit� komandin�je eilut�je nurodyt� fail� tik ra�ymui (sukurt�, jei n�ra, i�valyt� turin� jei jau yra);
    nukopijuot� i� skaitomo failo � ra�om� komandin�je eilut�je nurodyt� bait� skia�i� (jei tiek bait� n�ra � tiek kiek yra, t. y. vis� fail�) naudojant read() ir write();
    u�daryt� abu failus su close().

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <aio.h>

int vp_test();

int vp_test(){
   return 0;
}

int main( int argc, char * argv[] ){

	int from_file, to_file, size;
	char *buffer;
	buffer = malloc(sizeof(char));
	
	printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );

	if(argc != 4){ /*Ar yra nurodyta reiksme*/
		printf("Naudojimas:\n %s kopijuojamas_failas direktorija_i_kur_nukipijuoti baitu_skaicius\n", argv[0]);
		return 1;
	} 

	size = atoi(argv[3]); // nurodytas dydis
	
	// failas tik skaitymui is kur
	if((from_file = open(argv[1], O_RDONLY)) == -1){
		perror("from_file klaida");
		return -1;	
	}
	
	// failas rasymui, i kur
	if((to_file = open(argv[2], O_WRONLY | O_CREAT)) == -1){
		perror("to_file klaida");
		return -1;	
	}	

	
	if(read(from_file, buffer, size) == -1){
		perror("Nepavyko nuskaityti");
		close(from_file);
		close(to_file);
		return -1;
	}	

	if(write(to_file, buffer, size) != size){
		perror("Nepavyko irasyti");
		close(from_file);
		close(to_file);
		return -1;
	}	
	
	close(from_file);
	close(to_file);

	return 0;
}