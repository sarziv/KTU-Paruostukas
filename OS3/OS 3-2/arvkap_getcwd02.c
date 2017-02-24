/* Failas: arvkap_getcwd02.c */
/*

    Sukurkite C programà loginas_getcwd02.c (loginas pakeiskite á savo loginà), kuri:
        gautø ir atspausdintø einamo katalogo vardà su getcwd() (ir kvieèiant getcwd() naudotø pathconf(".",_PC_PATH_MAX) gràþinamà reikðmæ)
        atidarytø einamà katalogà su open(), ásimintø ir atspausdintø jo deskriptoriø
        nueitø á /tmp katalogà su chdir()
        patikrintø su getcwd() ir atspausdintø koks dabar yra einamasis katalogas
        gráþtø á 2-ame þingsnyje atidarytà katalogà su fchdir()
        ákelkite programà á Moodle

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