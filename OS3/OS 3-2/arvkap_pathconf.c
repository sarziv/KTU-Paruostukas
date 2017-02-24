/* Failas: arvkap_pathconf.c */
/*
Funkcijos pathconf() ir fpathconf() leidþia suþinoti konkreèios UNIX OS failø sistemos nustatymus (maksimalûs keliø ilgiai, maksimalus link'ø skaièius ir t.t.). Funkcijoms nurodomas kelias (failas arba katalogas) arba atidarytas deskriptorius.

    Sukurkite programà loginas_pathconf.c kuri pathconf() funkcijos pagalba suþinotø OS parametrus:
        Maksimalø failo vardo ilgá ( _PC_NAME_MAX ): ?
        Maksimalø kelio ilgá ( _PC_PATH_MAX ): ?
    Patikrinkite gautus rezultatus getconf komandos pagalba:

getconf NAME_MAX .
getconf PATH_MAX .

*/

#include <stdio.h>
#include <unistd.h>

int vp_test();

int vp_test(){
   return 0;
}

int main( int argc, char * argv[] ){

   printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );
   
   printf("Maksimalus failo vardo ilgis: %d\n", pathconf(".",  _PC_NAME_MAX));
   printf("Maksimalus kelio ilgis: %d\n", pathconf(".",  _PC_PATH_MAX));
   
   return 0;
}