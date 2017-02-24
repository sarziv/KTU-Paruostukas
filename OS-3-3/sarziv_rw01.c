/* Failas: sarziv_rw01.c */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int copy(const char *to, const char *from, int bytes);

int copy(const char *to, const char *from, int bytes) {
	int fd_to, fd_from;

	char *buffer;
	buffer = malloc(sizeof(char));

	if ((fd_from = open(from, O_RDONLY)) == -1) {
		perror("fd_from fail");
		return -1;
	}
	if ((fd_to = open(to, O_WRONLY | O_CREAT)) == -1) {
		close(fd_from);
		perror("fd_to fail");
		return -1;
	}

	if (read(fd_from, buffer, bytes) == -1) {
		perror("Nepavyko nuskaityti");
		close(fd_from);
		close(fd_to);
		return -1;
	}
	if (write(fd_to, buffer, bytes) != bytes) {
		perror("Nepavyko irasyti");
		close(fd_from);
		close(fd_to);
		return -1;
	}

	close(fd_from);
	close(fd_to);

	return 0;
}

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