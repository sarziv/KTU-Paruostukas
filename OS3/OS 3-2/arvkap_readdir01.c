/* Failas: arvkap_readdir01.c */
/*

    Sukurkite C programà loginas_readdir01.c (loginas pakeiskite á savo loginà), kuri:
        atidarytø einamà katalogà su opendir() arba fdopendir();
        cikle nuskaitytø visus katalogo áraðus su readdir() ir iðvestø kiekvieno áraðo i-node numerá (dirent struktûros d_ino laukas) ir failo vardà (dirent struktûros d_name laukas);
        uþdarytø katalogà su closedir();
        ákelkite programà á Moodle.

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