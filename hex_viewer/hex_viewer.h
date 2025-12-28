#ifndef HEX_VIEWER_H
#define HEX_VIEWER_H

#include <stdio.h>
// Use windows API: SetConsoleTextAttribute
#include <windows.h>

/* 16 byte format string special sign defined */
#define UNKNOW (11)
#define IS00 (2)
#define ISFF (24)

/* 
 * macro color_puts: print colorful string to command line
 */
#define color_puts(Str, Color) \
	do { \
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (Color)%16); \
		printf("%s", (Str)); \
	} while(0)
//

/* 
 * macro color_putchar: print colorful character to command line
 */
#define color_putchar(C, Color) \
	do { \
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (Color)%16); \
		printf("%c", (C)); \
	} while(0)
//

/* 
 * macro fourbit2hex: Convert a number smaller than 16 to a Hex character
 */
#define fourbit2hex(fourbit) \
	( ((fourbit) >= 0 && (fourbit) <= 9) ? \
		'0' + (fourbit) : \
		'A' + ((fourbit) - 10) \
	)
//

typedef unsigned char _Byte;


int hextab_print(FILE *stream);
int printline(size_t address, const char *hexstr, const char *asciistr);
const char *hextab16B(const _Byte *buf, size_t n);
const char *str16Bfmt(const _Byte *buf, size_t n);

static inline int get16B(_Byte *buf, FILE *stream)
{
	return fread(buf, 1, 16, stream);
}


#endif