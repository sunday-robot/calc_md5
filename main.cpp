#include <stdio.h>

#include "md5.h"

const size_t buf_size = 0x10000000;

static bool calc_md5(const char* file_path, unsigned char* digest) {
	auto fp = fopen(file_path, "rb");
	if (fp == NULL) {
		return false;
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
		digest[i] = md5ctx.digest[i];
	}

	return true;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage:\n%s <file path>...\n", argv[0]);
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		printf("%s\n    ", argv[i]);

		unsigned char digest[16];
		if (!calc_md5(argv[i], digest)) {
			printf("Failed to open file.\n");
		} else {
			for (auto i = 0; i < 16; i++) {
				printf("%02X", digest[i]);
			}
		}
		printf("\n");
	}

	printf("\nHit enter key.\n");
	(void)getchar();

	return 0;
}
