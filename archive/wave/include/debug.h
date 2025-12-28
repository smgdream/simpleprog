#define debug(num) fprintf(stderr, "Dot: %d\n", (num))
#define db32b(ptr, end) \
	fprintf(stderr, "%02hhX %02hhX %02hhX %02hhX\t %zu"#end, \
	  *((uint8_t *)(ptr)+0), *((uint8_t *)(ptr)+1), *((uint8_t *)(ptr)+2), *((uint8_t *)(ptr)+3), cnt/48000)
#define db24b(ptr, end) \
	fprintf(stderr, "%02hhX %02hhX %02hhX\t %zu"#end, \
	  *((uint8_t *)(ptr)+0), *((uint8_t *)(ptr)+1), *((uint8_t *)(ptr)+2), cnt/48000)
static unsigned long long cnt = 0;