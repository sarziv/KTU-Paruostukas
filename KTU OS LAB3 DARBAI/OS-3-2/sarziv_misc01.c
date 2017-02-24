/* Šarunas Živila KTU IFI-3 */
/* Failas: sarziv_misc01.c */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int sz_test();

int sz_test(){
   return 0;
}

int main( int argc, char * argv[] ){
	int fd;
	printf( "(C) Šarunas Živila, %s\n", __FILE__ );
	
	if(argc != 2){ /*Ar yra nurodyta reiksme*/
		printf("Naudojimas:\n %s failas ar katalogas\n", argv[0]);
		return 1;
	}
	
	if((fd = creat(argv[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1){ //creat() sukuriam faila
		printf("%s failas sukurtas\n", argv[1]);
	} else {
		printf("Error");
	}
	
	return 0;	
}