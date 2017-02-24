/* Failas: arvkap_frw01.c */
/*
Nukopijuokite loginas_rw01.c á loginas_frw01.c ir pakeiskite, kad vietoj open() bûtø naudojama fopen(), vietoj close() – fclose(), vietoj read() – fread(), vietoj write() – fwrite().
Iðbandykite naujà programà. Turëtø gautis toks pat rezultatas.
Kuo skiriasi fgetc() ir getc(
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
	if((from_file = fopen(argv[1], O_RDONLY)) == -1){
		perror("from_file klaida");
		return -1;	
	}
	
	// failas rasymui, i kur
	if((to_file = fopen(argv[2], O_WRONLY | O_CREAT)) == -1){
		perror("to_file klaida");
		return -1;	
	}	

	
	if(fread(from_file, buffer, size) == -1){
		perror("Nepavyko nuskaityti");
		fclose(from_file);
		fclose(to_file);
		return -1;
	}	

	if(fwrite(to_file, buffer, size) != size){
		perror("Nepavyko irasyti");
		fclose(from_file);
		fclose(to_file);
		return -1;
	}	
	
	fclose(from_file);
	fclose(to_file);

	return 0;
}