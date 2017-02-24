/* Failas: arvkap_readdir01.c */
/*

    Sukurkite C program� loginas_readdir01.c (loginas pakeiskite � savo login�), kuri:
        atidaryt� einam� katalog� su opendir() arba fdopendir();
        cikle nuskaityt� visus katalogo �ra�us su readdir() ir i�vest� kiekvieno �ra�o i-node numer� (dirent strukt�ros d_ino laukas) ir failo vard� (dirent strukt�ros d_name laukas);
        u�daryt� katalog� su closedir();
        �kelkite program� � Moodle.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

int vp_test();

int vp_test(){
   return 0;
}

int main( int argc, char * argv[] ){
   DIR *dir;
   struct dirent *ent;
   printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );
   
   if((dir = opendir(".")) != NULL){
	   while((ent = readdir(dir)) != NULL){ 
			printf("Failo pavadinimas: %s, i-node: %ld \n", ent->d_name, ent->d_ino);
	   }
	   closedir(dir);
   }
   return 0;
}