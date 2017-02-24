/* Failas: sarziv_mmap01.c */

#ifndef SARZIV_MMAP01_C
#define SARZIV_MMAP01_C

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>

int sz_test_openw(const char *name);
void* sz_test_mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);
int sz_test_munamp(void *a, int size);
int sz_test_usemaped(void *a, int size);

#if __INCLUDE_LEVEL__ == 0
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 1048576

int main(int argc, char * argv[]) {
	int d;
	void *a = NULL;
	printf("(C) Sarunas Zivila, %s\n", __FILE__);
	if (argc != 2) {
		printf("Naudojimas:\n %s failas\n", argv[0]);
		exit(255);
	}
	if ((d = sz_test_open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0640)) == 0)
		printf("dskr = %d\n", d);
	a = sz_test_mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, d, 0);
	sz_test_usemaped(a, SIZE);
	sz_test_munamp(a, SIZE);
	if (sz_test_close(d) == 0)
		puts("closed");
	return 0;
}
#endif

void* sz_test_mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off) {
	void *a = NULL;
	sz_test_lseek(fildes, len - 1, SEEK_SET);
	sz_test_write(fildes, &fildes, 1); /* iraso bile ka i failo gala */
	a = mmap(addr, len, prot, flags, fildes, off);
	if (a == MAP_FAILED) {
		perror("mmap failed");
		abort();
	}
	return a;
}
int sz_test_munamp(void *a, int size) {
	int rv;
	rv = munmap(a, size);
	if (rv != 0) {
		puts("munmap failed");
		abort();
	}
	return 1;
}
int sz_test_usemaped(void *a, int size) {
	memset(a, 0xF0, size);
	return 1;
}
#endif