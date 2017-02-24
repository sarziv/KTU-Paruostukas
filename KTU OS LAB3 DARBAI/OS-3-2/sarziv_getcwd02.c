/* �arunas �ivila KTU IFI-3 */
/* Failas: sarziv_getcwd02. */

/*
Kodel kvieciama free(cwd): ?
PASTABA: getcwd() veikimas, kai pirmu parametru nurodyta NULL � nestandartinis, kaip veikia �r.: getcwd(3C) os.if.ktu.lt ma�inoje.

Sukurkite C programa loginas_getcwd02.c (loginas pakeiskite i savo logina), kuri:
gautu ir atspausdintu einamo katalogo varda su getcwd() (ir kvieciant getcwd() naudotu pathconf(".",_PC_PATH_MAX) gra�inama reik�me)
atidarytu einama kataloga su open(), isimintu ir atspausdintu jo deskriptoriu
nueitu i /tmp kataloga su chdir()
patikrintu su getcwd() ir atspausdintu koks dabar yra einamasis katalogas
gri�tu i 2-ame �ingsnyje atidaryta kataloga su fchdir() (ir patikrintu/parodytu, kad tikrai gri�o)

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int sz_test();

int sz_test(){
   return 0;
}


int main( int argc, char * argv[] ){
   int dirkrip;
   char *katalogas = getcwd(NULL, pathconf(".", _PC_PATH_MAX));

   printf( "(C) �arunas �ivila, %s\n", __FILE__ );
   
   printf("Naudojamas katalogas: %s\n", katalogas);
   dirkrip = open(katalogas, O_RDONLY);
   printf("Einamasis katalogas: %d\n", dirkrip);
   
   chdir("/tmp"); // tmp
   printf("tmp katalogas su (chdir): %s\n", getcwd(NULL, pathconf(".", _PC_PATH_MAX))); // print tmp
   
   fchdir(open(katalogas, O_RDONLY)); // atidaro kataloga
   printf("fchdir: %s\n", getcwd(NULL, pathconf(".", _PC_PATH_MAX)));  
   
   return 0;
}