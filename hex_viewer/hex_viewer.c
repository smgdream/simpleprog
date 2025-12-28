#include <stdio.h>
#include <ctype.h>
#include "hex_viewer.h"

/*
 * by Smgdream
 * version 0.2.1
*/

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	
	printf("Hex Viewer by smgdream\n\n");

	if (argc == 1) {
		printf("No file\n");
		printf("Usage: %s <FILE>\n", argv[0]);
		return 1;
	}

	// fp = fopen("inside_res.exe", "rb");
	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		printf("No file\n");
		return 0;
	}
	
	printf("\n\nFile: %s\n\n", argv[1]);
	hextab_print(fp);

	fclose(fp);
	return 0;
}


/*
 * hextab_print: print the hex tab row by row
 */
int hextab_print(FILE *stream)
{
	int size = 0;
	_Byte buf_16B[16];

	color_puts("           00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  0123456789ABCDEF\n", 12);
	printf("\n");
	for (size_t adr = 0 ; (size = get16B(buf_16B, stream)); adr += 16)
		printline(adr, hextab16B(buf_16B, size), str16Bfmt(buf_16B, size));

	return 1;
}


/* 
 * printline: print a hex row with color
 */
int printline(size_t addr, const char *hexstr, const char *asciistr)
{
	int i = 0;
	char hexunit[] = "00 ";
	char tmpstr[32+1];

	sprintf(tmpstr, "%08llX   ", addr);
	color_puts(tmpstr, 12);
	for (i = 0; hexstr[i]; i += 3) {
		if (i / 3 == 8) {
			putchar(' ');
			++i;
		}
		hexunit[0] = hexstr[i];
		hexunit[1] = hexstr[i+1];
		hexunit[2] = ' ';
		hexunit[3] = '\0';

		if (asciistr[i/3] == UNKNOW) {
			color_puts(hexunit, 9);
			continue;
		} else if (hexunit[0] == '0' && hexunit[1] == '0') {
			color_puts(hexunit, 8);
			continue;
		} else if (hexunit[0] == 'F' && hexunit[1] == 'F') {
			color_puts(hexunit, 12);
			continue;
		} else
			color_puts(hexunit, 7);
	}
	if (i == 49)
		putchar('\b');
	while (i++ < 48)
		putchar(' ');

	printf("  ");

	color_puts("", 7); /* Set as default color */
	for (;*asciistr; ++asciistr) {
		if (*asciistr == UNKNOW) {
			color_putchar(',', 9);
			continue;
		} else if (*asciistr == IS00) {
			color_putchar('.', 8);
			continue;
		} else if (*asciistr == ISFF) {
			color_putchar(',', 12);
			continue;
		} else
			color_putchar(*asciistr, 7);
	}
	color_puts("\n", 7); /* Set as default color */

	return 1;
}


/* 
 * hextab16B: get a formetting hex row
 */
const char *hextab16B(const _Byte *buf, size_t n)
{
	static char hexrow[] = "00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F";
	int i = 0;

	for (i = 0; i/3 < n; ++buf, i += 3) { /* Although it add 1 after middle but it dev 3. So it can exec normally */
		if (i / 3 == 8) /* add a space in the middle of the hextab */
			hexrow[i++] = ' ';
		hexrow[i+0] = fourbit2hex(*buf >> 4); /* high 4 bit */
		hexrow[i+1] = fourbit2hex(*buf & 0x0F); /* low 4 bit */
		hexrow[i+2] = ' ';
	}
	hexrow[i-1] = '\0';

	return hexrow;
}

/* 
 * str16Bfmt: get a 16 byte formatting string
 */
const char *str16Bfmt(const _Byte *buf, size_t n)
{
	static char fmtstr[16+1];
	int i = 0;

	for (i = 0; i < n; ++buf)
		fmtstr[i++] = isprint(*buf) ? \
				*buf : \
			(*buf == 0) ? \
				IS00 : \
			(*buf == 0xFF) ? \
				ISFF : \
				UNKNOW; 
	fmtstr[i] = '\0';

	return fmtstr;
}
