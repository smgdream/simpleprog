#include <stdio.h>
#include <ctype.h>


typedef unsigned char _Byte;

int puthex(FILE *stream);
const char *hextab16B(const _Byte *buf, size_t n);
const char *str16Bfmt(const _Byte *buf, size_t n);


int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	

	if (argc == 1) {
		printf("No file\n");
		return 1;
	}

	// fp = fopen("inside_res.exe", "rb");
	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		printf("No file\n");
		return 0;
	}
	
	printf("\n\nFile: %s\n\n", argv[1]);
	puthex(fp);

	fclose(fp);
	printf("\nEnter to exit\n");
	getchar();

	return 0;
}

static inline int get16B(_Byte *buf, FILE *stream)
{
	return fread(buf, 1, 16, stream);
}

int puthex(FILE *stream)
{
	int size = 0;
	_Byte buf_16B[16];

	printf("Address    00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n");
	printf("\n");
	for (size_t adr = 0 ; size = get16B(buf_16B, stream); adr += 16)
		printf("%08.8llX:  %-48.48s  %s\n", adr, hextab16B(buf_16B, size), str16Bfmt(buf_16B, size));
	return 1;
}


#define fourbit2hex(fourbit) \
	( ((fourbit) >= 0 && (fourbit) <= 9) ? \
		'0' + (fourbit) : \
		'A' + ((fourbit) - 10) \
	)

const char *hextab16B(const _Byte *buf, size_t n)
{
	static char hextab[] = "00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F";
	int i = 0;

	for (i = 0; i/3 < n; ++buf, i += 3) {
		if (i / 3 == 8) /* add a space in the middle of the hextab */
			hextab[i++] = ' ';
		hextab[i+0] = fourbit2hex(*buf >> 4); /* high 4 bit */
		hextab[i+1] = fourbit2hex(*buf & 0x0F); /* low 4 bit */
		hextab[i+2] = ' ';
	}
	hextab[i-1] = '\0';

	return hextab;
}

const char *str16Bfmt(const _Byte *buf, size_t n)
{
	static char fmtstr[16+1];
	int i = 0;

	for (i = 0; i < n; ++buf)
		fmtstr[i++] = isprint(*buf) ? *buf : (*buf != '\0' ? '?' : '.'); 
	fmtstr[i] = '\0';

	return fmtstr;
}
