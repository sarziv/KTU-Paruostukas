/* Failas: arvkap_rw01.c */
/*
Sukurkite program� loginas_seek01.c, kuri:

    sukurt� fail� (su open() ar creat());
    nueit� � 1MB gilyn � fail� su lseek();
    �ra�yt� 1 bait�;
    u�daryt� fail� su close().

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

	int file;
	char *buffer;
	buffer = malloc(sizeof(char));
	
	printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );

	if(argc != 2){ /*Ar yra nurodyta reiksme*/
		printf("Naudojimas:\n %s failo_pavadinimas\n", argv[0]);
		return 1;
	} 

	// Failo sukurimas
	if((file = open(argv[1], O_WRONLY | O_CREAT)) == -1){
		perror("file klaida");
		return -1;	
	}	
	
	// "ejimas"
	if((lseek(file, 1024, SEEK_SET)) == -1){
		perror("lseek klaida");
		return -1;
	}
	
	// Irasymas
	if((write(file, buffer, 1)) == -1){
		perror("write klaida");
		close(file);
		return -1;
	}

	close(file);
	
	return 0;
}