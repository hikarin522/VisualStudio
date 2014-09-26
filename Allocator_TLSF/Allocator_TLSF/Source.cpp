#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef struct TAG tag_t;
struct TAG
{
	size_t size;
	void *point;
	tag_t *next;
	tag_t *pre;
};

uint8_t memstor[1024 * 2];

tag_t free_list = {sizeof(memstor), memstor, &free_list, &free_list};
tag_t use_list = {0, NULL, &use_list, &use_list};


void print_mem(void);
void print_size(void);

tag_t *BTX_new(size_t);
void BTX_free(tag_t*);

int main(void)
{
	tag_t *t[16];
	printf("hello\n");
	print_size();
	print_mem();

	for (uint8_t j = 0; j < 4; j++)
	{
		t[j] = BTX_new(8);
		for (uint8_t i = 0; i < 8; i++)
		{
			((uint8_t *)t[j]->point)[i] = i + j;
		}
		print_mem();
		BTX_free(t[j]);
		print_mem();
	}
	
	
	return 0;
}

void BTX_free(tag_t *delData)
{
	delData->next->pre = delData->pre;
	delData->pre->next = delData->next;

	tag_t *it;
	for (it = free_list.next; it != &free_list; it = it->next)
	{
		if (it->point < delData->point)
			break;
	}

	it->pre->next = delData;
	delData->pre = it->pre;
	it->pre = delData;
	delData->next = it;

	if (delData->pre != &free_list && delData->pre->point == (uint8_t *)delData->point + delData->size)
	{
		delData->size += delData->pre->size;
		delData->pre->size = 0;
		delData->pre->point = NULL;
	}

	if ((uint8_t *)delData->next->point + delData->next->size == delData->point)
	{
		delData->next->size += delData->size;
		delData->size = 0;
		delData->point = NULL;
	}

	for (it = (tag_t *)free_list.point - 1; it >= (tag_t *)memstor && it->size == 0; it--)
	{
		it->next->pre = it->pre;
		it->pre->next = it->next;
		free_list.point = it;
		free_list.size += sizeof(tag_t);
	}
}

tag_t *BTX_new(const size_t size)
{
	if (free_list.next == &free_list)
	{
		tag_t *const tmp = (tag_t *)free_list.point;
		
		if (free_list.size < sizeof(tag_t) + size)
			return NULL;

		free_list.size -= sizeof(tag_t) + size;
		free_list.point = tmp + 1;

		tmp->size = size;
		tmp->point = (uint8_t *)free_list.point + free_list.size;

		use_list.pre->next = tmp;
		tmp->pre = use_list.pre;
		use_list.pre = tmp;
		tmp->next = &use_list;

		return tmp;
	}
}


void print_mem(void)
{
	int i, j;
	char str[16];
	printf("\nfree_list : & %#x, size %d, point %#x, next %#x, pre %#x\n", &free_list, free_list.size, free_list.point, free_list.next, free_list.pre);
	printf("use_list  : & %#x, size %d, point %#x, next %#x, pre %#x\n", &use_list, use_list.size, use_list.point, use_list.next, use_list.pre);
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
	printf("sizeof(tag_t) : %dbyte\n", sizeof(tag_t));
	printf("sizeof(memstor) : %dbyte (%#x)\n", sizeof(memstor), sizeof(memstor));
}
