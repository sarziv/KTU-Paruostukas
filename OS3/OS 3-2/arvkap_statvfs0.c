/* Failas: arvkap_statvfs0.c */
/*
Ðios funkcijos panaðios á stat() ir fstat(), tik gràþina informacija ne apie nurodytà failà, o apie failø sistemà, kurioje tas failas yra.

    Nukopijuokite loginas_stat01.c á loginas_statvfs01.c ir papildykite, kad papildomai bûtø iðvedama ir statvfs() arba fstatvfs() gràþinamos struktûros statvfs informacija:
        failø sistemos bloko dydis
        failø sistemos tipas (f_basetype, nestandartinis laukas statvfs gràþinamoje struktûroje, þr. man statvfs ant os.if.ktu.lt)
        failø sistemos dydis
        maksimalø failo kelio/vardo ilgis
    Sukurtà programà ákelkite á Moodle.

*/

#include <unistd.h>
#include <stdio.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int vp_test();

int vp_test(){
   return 0;
}

int main( int argc, char * argv[] ){
	struct stat *buf = malloc(sizeof(struct stat));
	struct statvfs *bufvfs = malloc(sizeof(struct statvfs));
	
	printf( "(C) 2013 Arvydas Kapacinskas, %s\n", __FILE__ );
	
	if(argc != 2){ /*Ar yra nurodyta reiksme*/
		printf("Naudojimas:\n %s failas_ar_katalogas\n", argv[0]);
		exit(255);
	}
	
	stat(argv[1], buf);
	
	printf("Failas ar katalogas: '%s'\n", argv[1]);
	printf("Savininko ID: %d\n", buf->st_uid);
	printf("Dydis (baitais): %ld\n", buf->st_size);
	printf("i-node: %ld\n", buf->st_ino);
    printf("Failo teises: \t");
    printf((S_ISDIR(buf->st_mode)) ? "d" : "-");
    printf((buf->st_mode & S_IRUSR) ? "r" : "-");
    printf((buf->st_mode & S_IWUSR) ? "w" : "-");
    printf((buf->st_mode & S_IXUSR) ? "x" : "-");
    printf((buf->st_mode & S_IRGRP) ? "r" : "-");
    printf((buf->st_mode & S_IWGRP) ? "w" : "-");
    printf((buf->st_mode & S_IXGRP) ? "x" : "-");
    printf((buf->st_mode & S_IROTH) ? "r" : "-");
    printf((buf->st_mode & S_IWOTH) ? "w" : "-");
    printf((buf->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");	
	printf("Failo tipas: %s\n", (S_ISREG(buf->st_mode)) ? "paprastas failas" : "katalogas");
	printf("--------------------------------\n");
	
	statvfs(argv[1], bufvfs);
	
	printf("Failu sistemos bloko dydis: %ld\n", bufvfs->f_bsize);
	printf("Failu sistemos tipas: %s\n", bufvfs->f_fstr);
	printf("Failu sistemos dydis: %ld\n", bufvfs->f_frsize);
	printf("Maksimalu failo kelio/vardo ilgis: %ld\n", bufvfs->f_namemax);
	
	free(buf);
	free(bufvfs);
	
	return 0;
}

/*
PVZ: 
argv[0] - a.out
argv[1] - reiksme (pvz) 'a.out reiksme'
*/