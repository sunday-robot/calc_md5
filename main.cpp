#include <stdio.h>

#include "md5.h"

const size_t buf_size = 0x10000000;

int main(int argc, char* argv[]) {
	auto fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		return 1;
	}

	auto buf = new unsigned char[buf_size];

	MD5_CTX md5ctx;
	MD5Init(&md5ctx);
	do {
		auto len = fread(buf, 1, buf_size, fp);
		MD5Update(&md5ctx, buf, len);
	} while (!feof(fp));
	fclose(fp);
	MD5Final(&md5ctx);

	for (auto i = 0; i < 16; i++) {
		printf("%02X", md5ctx.digest[i]);
	}
	printf("\n");
	(void)getchar();

	return 0;
}
