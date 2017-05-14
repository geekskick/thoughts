#include <stdio.h>
#include <stdlib.h>

typedef uint32_t reg_addr;

enum args{ NAME, REG_OFFS, BIT, COUNT };

void print_usage( void )
{
	printf("Usage: ./bba_converter <register offset from gpio base> <bit>\n");
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

	if( argc != COUNT ) { print_usage(); }

	reg_addr port_offset = strtol(argv[REG_OFFS],NULL, 16);
	int bit = atoi(argv[BIT]);

	printf("Port %d:%d alias is 0x%x\n", port_offset, bit, ALIAS_REGION_BASE + (REG_WIDTH * (port_offset+GPIO_OFFSET) )+ ( BIT_OFFET * bit) );

	return 0;
}