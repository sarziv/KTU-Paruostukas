/*sarziv_mmap02.c*/

#ifndef SARZIV_MMAP02_C
#define SARZIV_MMAP02_C

#include <aio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>


char *sz_map(int d, int size, int read);
int sz_test_fstat(int fd, struct stat *buf);

#if __INCLUDE_LEVEL__ == 0

void sz_exit(int code);
int rd;
int wd;

int main(int argc, char *argv[]) {
	int s;
	struct stat status;
	void *rm, *wm;
	printf("(C) Sarunas Zivila, %s\n", __FILE__);
	if (argc < 3) {
		printf("Reikia 2 argumentu: skaitymui ir rasymui\n");
		sz_exit(1);
	}

	if ((rd = sz_test_open(argv[1], O_RDONLY)) == -1)
		sz_exit(1);

	if ((wd = sz_test_open(argv[2], O_RDWR | O_CREAT, S_IRWXU | S_IWGRP | S_IROTH)) == -1)
		sz_exit(1);

	if (sz_test_fstat(rd, &status) == -1)
		sz_exit(1);
	s = status.st_size;
	printf("Dydis - %d baitu\n", s);
	rm = sz_map(rd, s, 1);
	wm = sz_map(wd, s, 0);
	memcpy(wm, rm, s);
	if (sz_test_munamp(rm, s) == -1)
		sz_exit(1);
	if (sz_test_munamp(wm, s) == -1)
		sz_exit(1);
	sz_exit(0);
	return 0;
}

void sz_exit(int code) {
	close(rd);
	close(wd);
	exit(code);
}
#endif

char *sz_map(int d, int size, int read) {
	void *buf;
	if (!read) {
		sz_test_lseek(d, size - 1, SEEK_SET);
		sz_test_write(d, &d, 1);
		buf = sz_test_mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, d, 0);
	}
	else {
		buf = sz_test_mmap(NULL, size, PROT_READ, MAP_SHARED, d, 0);
	}
	if (buf == MAP_FAILED)
		sz_exit(1);
	return buf;
}

int sz_test_fstat(int fd, struct stat *buf) {
	if (fstat(fd, buf) == -1) {
		perror("fstat() failed");
	}
	return 0;
}
#endif