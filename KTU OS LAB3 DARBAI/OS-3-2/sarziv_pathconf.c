/* Šarunas Živila KTU IFI-3 */
/* Failas: sarziv_pathconf.c */

/* 
Funkcijos pathconf() ir fpathconf() leidžia sužinoti konkrecios UNIX OS failu sistemos nustatymus 
(maksimalus keliu ilgiai, maksimalus link'u skaicius ir t.t.).
 Funkcijoms nurodomas kelias (failas arba katalogas) arba atidarytas deskriptorius.

getconf NAME_MAX .
getconf PATH_MAX .
*/
#include <stdio.h>
#include <unistd.h>

int sz_test();

int sz_test(){
   return 0;
}

int main( int argc, char * argv[] ){

   printf( "(C) Šarunas Živila, %s\n", __FILE__ );
   
   printf("Max file name %ld\n", pathconf(".",  _PC_NAME_MAX));

   printf("Max path length %ld\n", pathconf(".",  _PC_PATH_MAX));
   
   return 0;
}