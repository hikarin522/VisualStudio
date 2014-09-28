#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed long int32_t;
typedef signed long long int64_t;

typedef int32_t ssize_t;

uint8_t memstor[1024];

struct Bondary_Tag;
typedef Bondary_Tag tag_t;

struct Bondary_Tag
{
	ssize_t size;
	tag_t *next;
	tag_t *pre;
	tag_t *back;
};

uint8_t get_bit_count(size_t val)
{
	size_t val1, val2;
	
	val1 = val & 0x55555555;
	val2 = (val >> 1) & 0x55555555;
	val = val1 + val2;
	val1 = val & 0x33333333;
	val2 = (val >> 2) & 0x33333333;
	val = val1 + val2;
	val1 = val & 0x0f0f0f0f;
	val2 = (val >> 4) & 0x0f0f0f0f;
	val = val1 + val2;
	val1 = val & 0x00ff00ff;
	val2 = (val >> 8) & 0x00ff00ff;
	val = val1 + val2;
	val1 = val & 0x0000ffff;
	val2 = (val >> 16) & 0x0000ffff;
	val = val1 + val2;

	return val;
}

uint8_t get_MSB(size_t val)
{
	if (val == 0)
		return -1;
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;

	return get_bit_count(val) - 1;
}


void print_mem(void);
void print_size(void);

void print_bit(size_t);

int main(void)
{
	printf("hello\n");
	print_size();
	print_mem();
	while (1)
	{
		int i;
		printf("\n");
		scanf("%d", &i);
		printf("\n%d = %#x = ", i, i);
		print_bit(i);
		printf("\ncount = %d\n", get_bit_count(i));
	}

	return 0;
}

void print_bit(size_t val)
{
	printf("0b");
	for (int i = 0; i < sizeof(size_t) * 8; i++)
	{
		printf(val & 0x80000000 ? "1" : "0");
		val <<= 1;
	}
}

void print_mem(void)
{
	int i, j;
	char str[16];
	printf("\n");
	printf("memstor : %#x - %#x\n", memstor, memstor + sizeof(memstor));
	for (i = 0; i < sprintf(str, "%#x :", memstor); i++)
		printf(" ");
	for (j = 0; j < 64; j++)
		printf(" %2x", j);
	printf("\n");
	for (i = 0; i < sizeof(memstor);)
	{
		printf("%#x :", memstor + i);
		for (j = 0; j < 64; j++)
			printf(" %02hhx", memstor[i++]);
		printf("\n");
	}
	printf("\n");
	return;
}

void print_size(void)
{
	printf("sizeof(uint8_t) : %dbyte\n", sizeof(uint8_t));
	printf("sizeof(uint16_t) : %dbyte\n", sizeof(uint16_t));
	printf("sizeof(uint32_t) : %dbyte\n", sizeof(uint32_t));
	printf("sizeof(uint64_t) : %dbyte\n", sizeof(uint64_t));
	printf("sizeof(void *) : %dbyte\n", sizeof(void *));
	printf("sizeof(size_t) : %dbyte\n", sizeof(size_t));
	printf("sizeof(memstor) : %dbyte (%#x)\n", sizeof(memstor), sizeof(memstor));
}
