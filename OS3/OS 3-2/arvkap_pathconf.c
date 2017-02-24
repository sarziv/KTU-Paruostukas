/* Failas: arvkap_pathconf.c */
/*
Funkcijos pathconf() ir fpathconf() leid�ia su�inoti konkre�ios UNIX OS fail� sistemos nustatymus (maksimal�s keli� ilgiai, maksimalus link'� skai�ius ir t.t.). Funkcijoms nurodomas kelias (failas arba katalogas) arba atidarytas deskriptorius.

    Sukurkite program� loginas_pathconf.c kuri pathconf() funkcijos pagalba su�inot� OS parametrus:
        Maksimal� failo vardo ilg� ( _PC_NAME_MAX ): ?
        Maksimal� kelio ilg� ( _PC_PATH_MAX ): ?
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