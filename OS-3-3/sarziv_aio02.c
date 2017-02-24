/* Failas: sarziv_aio02.c */

#ifndef SARZIV_AIO02_C
#define SARZIV_AIO02_C

#include <aio.h>

int sz_read_bytes(int desc, struct aiocb *block, char *buf, int bufOffset, int bytes);
int sz_read_wait(struct aiocb *block);

#if __INCLUDE_LEVEL__ == 0
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "../uzd2/sarziv_open01.c"
#include "sarziv_aio01.c"
static const int bufferSize = 1048576;

int rd;
void sz_exit(int code);

int main() {
	struct aiocb block;
	char *buf;
	int n = 0, t;
	buf = malloc(bufferSize);
	printf("(C) Sarunas Zivila, %s\n", __FILE__);
	rd = sz_test_open("/dev/urandom", O_RDONLY);
	if (rd == -1) {
		printf("Klaida atidarinejant faila\n");
		sz_exit(1);
	}
	while (n < bufferSize) {
		if (sz_read_bytes(rd, &block, buf, n, bufferSize - n) != 0)
			sz_exit(1);
		t = sz_read_wait(&block);
		if (t > 0) {
			n += t;
			printf("Perskaityta %d baitu\n", n);
		}
		else
			sz_exit(1);
	}
	sz_exit(0);
	return 0;
}
#endif
void sz_exit(int code) {
	sz_test_close(rd);
	exit(code);
}

int sz_read_bytes(int desc, struct aiocb *block, char *buf, int bufOffset, int bytes) {
	memset((void*)block, 0, sizeof(struct aiocb));
	block->aio_fildes = desc;
	block->aio_buf = buf + bufOffset;
	block->aio_nbytes = bytes;
	block->aio_offset = 0;
	if (sz_test_aio_read(block) != 0) {
		printf("Klaida skaitymo pradzioje\n");
		return -1;
	}
	return 0;
}

int sz_read_wait(struct aiocb *block) {
	const struct aiocb *temp[1];
	temp[0] = block;
	if (sz_test_aio_suspend(temp, 1, NULL) != 0) {
		printf("Klaida skaitymo pabaigoje\n");
		return -1;
	}
	return sz_test_aio_return(block);
}

#endif