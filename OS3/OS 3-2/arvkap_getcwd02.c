/* Failas: arvkap_getcwd02.c */
/*

    Sukurkite C program� loginas_getcwd02.c (loginas pakeiskite � savo login�), kuri:
        gaut� ir atspausdint� einamo katalogo vard� su getcwd() (ir kvie�iant getcwd() naudot� pathconf(".",_PC_PATH_MAX) gr��inam� reik�m�)
        atidaryt� einam� katalog� su open(), �simint� ir atspausdint� jo deskriptori�
        nueit� � /tmp katalog� su chdir()
        patikrint� su getcwd() ir atspausdint� koks dabar yra einamasis katalogas
        gr��t� � 2-ame �ingsnyje atidaryt� katalog� su fchdir()
        �kelkite program� � Moodle

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int vp_test();

int vp_test(){
   return 0;
}


int main( int argc, char * argv[] ){
   int dskr;
   char *katalogas = getcwd(NULL, pathconf(".", _PC_PATH_MAX));

   printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );
   
   printf("Naudojamas katalogas: %s\n", katalogas);
   dskr = open(katalogas, O_RDONLY);
   printf("Einamo katalogo deskriptorius: %d\n", dskr);
   
   chdir("/tmp"); // atidaro kataloga
   printf("tmp katalogas su (chdir): %s\n", getcwd(NULL, pathconf(".", _PC_PATH_MAX))); // spausdina /tmp
   
   fchdir(open(katalogas, O_RDONLY)); // atidaro kataloga
   printf("fchdir: %s\n", getcwd(NULL, pathconf(".", _PC_PATH_MAX)));  
   
   return 0;
}