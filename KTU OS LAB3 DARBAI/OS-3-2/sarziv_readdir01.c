/* �arunas �ivila KTU IFI-3 */
/* Failas: sarziv_readdir01.c */

/*
atidarytu einama kataloga su opendir() arba fdopendir();
cikle nuskaitytu visus katalogo ira�us su readdir() ir i�vestu kiekvieno ira�o i-node numeri 
(dirent strukturos d_ino laukas) 
ir failo varda (dirent strukturos d_name laukas);
u�darytu kataloga su closedir();
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

int sz_test();

int sz_test(){
   return 0;
}

int main( int argc, char * argv[] ){
   DIR *dir;
   struct dirent *enter;
   printf( "(C) �arunas �ivila , %s\n", __FILE__ );
   
   if((dir = opendir(".")) != NULL){
	   while((enter = readdir(dir)) != NULL){ 
			printf("Failo pavadinimas: %s, i-node: %ld \n", enter->d_name, enter->d_ino);
	   }
	   closedir(dir);
   }
   return 0;
}