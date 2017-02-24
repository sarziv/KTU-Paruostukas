/* Failas: sarziv_frw01.c */

#ifndef SARZIV_FRW01_C
#define SARZIV_FRW01_C

#include <stdio.h>
#include <fcntl.h>

FILE *sz_test_fopen(const char *filename, const char *mode);
int sz_test_fclose(FILE *stream);
int sz_test_fread(void *ptr, size_t size, size_t nitems, FILE *stream);
int sz_test_fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream);
int copy(const char *to, const char *from, int bytes);


#if __INCLUDE_LEVEL__ == 0
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>

#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char **argv) {

	int bytes;
	if (argc != 4) {
		printf("Komandos sablonas:\n %s kopijuojamas_failas direkotorija_i_kur_kopijuojama baitu_skaicius\n", argv[0]);
		return 1;
	}
	bytes = atoi(argv[3]);
	printf("Baitai skaicium %i\n", bytes);
	copy(argv[2], argv[1], bytes);

	return 0;
}
#endif

FILE *sz_test_fopen(const char *filename, const char *mode) {
	FILE *fd_from;
	if ((fd_from = fopen(filename, mode)) == NULL) {
		perror("fd_from fail");
		return NULL;
	}
	return fd_from;
}

int sz_test_fclose(FILE *stream) {
	if (fclose(stream) == EOF) {
		perror("fclose fail");
		return -1;
	}
	return 0;
}
int sz_test_fread(void *ptr, size_t size, size_t nitems, FILE *stream) {
	if (fread(ptr, size, nitems, stream) == NULL) {
		perror("Nepavyko nuskaityti");
		sz_test_fclose(stream);
		return -1;
	}
	return 0;
}

int sz_test_fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream) {
	if (fwrite(ptr, size, nitems, stream) != nitems) {
		perror("Nepavyko irasyti");
		sz_test_fclose(stream);
		return -1;
	}
	return 0;
}

int copy(const char *to, const char *from, int bytes) {
	FILE *fd_to, *fd_from;

	char *buffer;
	buffer = malloc(sizeof(char));

	fd_from = sz_test_fopen(from, "r");

	fd_to = sz_test_fopen(to, "w+");

	if (fread(buffer, 1, bytes, fd_from) == -1)
		sz_test_fclose(fd_to);

	if (fwrite(buffer, 1, bytes, fd_to) == -1)
		sz_test_fclose(fd_from);

	fclose(fd_from);
	fclose(fd_to);

	return 0;
}
#endif