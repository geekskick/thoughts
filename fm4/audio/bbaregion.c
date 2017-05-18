#include <stdio.h>
#include <stdlib.h>

typedef uint32_t reg_addr;

enum args{ NAME, REG_OFFS, BIT, OPT_NB, COUNT };

void print_usage( void )
{
	printf("Usage: ./bba_converter <register offset from gpio base> <bit> <optional new base>\n");
	exit(1);
}

int main(int argc, const char* argv[])
{
	static const reg_addr ALIAS_REGION_BASE = 0x42000000;
	static const reg_addr PERIPH_REGION_BASE = 0x40000000;
	static const reg_addr GPIO_REGION_BASE = 0x4006F000;
	static const reg_addr GPIO_OFFSET = GPIO_REGION_BASE - PERIPH_REGION_BASE;
	static const uint8_t REG_WIDTH = 32;
	static const reg_addr BIT_OFFET = REG_WIDTH/8;

	if( argc != COUNT && argc != OPT_NB ) { print_usage(); }

	reg_addr port_offset = strtol(argv[REG_OFFS],NULL, 16);
	uint8_t bit = strtol(argv[BIT],NULL, 16);

	reg_addr base = GPIO_REGION_BASE;
	reg_addr offs = GPIO_OFFSET;

	if(argc == COUNT){ base = strtol(argv[OPT_NB],NULL, 16); offs = base - PERIPH_REGION_BASE; }


	printf("%X:%X bit:%d alias is 0x%X\n", base, offs, bit, ALIAS_REGION_BASE + (REG_WIDTH * (port_offset+offs) )+ ( BIT_OFFET * bit) );

	return 0;
}