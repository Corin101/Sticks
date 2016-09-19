#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void allocate_pool(struct mind *mentis, unsigned pool_size) {
	int cnt;

		if (mentis->sticks == 0) {
			mentis->sticks = pool_size;
			memset(mentis->memory, 0, sizeof(mentis->memory));
			return;
		}
		mentis->pool_size = pool_size;
		mentis->sticks = pool_size;
		mentis->pool = malloc(sizeof(list_t) * mentis->pool_size);
		mentis->memory = calloc(mentis->pool_size, sizeof(list_element_t));
		for(cnt=0;cnt != pool_size;++cnt) {
			mentis->pool[cnt] = list_new();
			list_fill(mentis->pool[cnt],cnt);
		}
}

void list_fill(list_t list,int cnt) {

	if (cnt == 0) {
		list_add(list,1);
		return;
	}
	if (cnt == 1) {
		list_add(list,1);
		list_add(list,2);
		return;
	}

	list_add(list,1);
	list_add(list,2);
	list_add(list,3);
}

void delete_pool(struct mind *mentis) {
	int cnt;
	for(cnt = 0;cnt != mentis->pool_size;++cnt)
		list_delete(mentis->pool[cnt]);
	free(mentis->pool);
	free(mentis->memory);
	free(mentis);
}

void learn_new(struct mind *mentis, int victory_status) {
	int cnt;
	if (victory_status == 0) 
		for(cnt = 0;cnt != mentis->pool_size-1;++cnt)
			if (mentis->memory[cnt] != 0)
				mem_remove(mentis, cnt, mentis->memory[cnt]);
	if (victory_status)
		for(cnt = 0;cnt != mentis->pool_size-1;++cnt)
			if (mentis->memory[cnt] != 0)
				mem_learn(mentis, cnt, mentis->memory[cnt]);
}

void mem_remove(struct mind *mentis, int cnt, list_element_t number) {
	list_t list;
	list_element_t buffer;
	list_iterator_t iter;
	int flag = 0;

	list = mentis->pool[cnt];
	for(iter = list_iterator(list);list_iterator_is_valid(iter);list_iterator_next(iter)) {
		buffer = list_get(iter);
		if (buffer == number)
			++flag;
		if (flag > 1) {
			list_remove(iter);
			break;
		}
	}
	list_iterator_delete(iter);
}

void mem_learn(struct mind *mentis, int cnt, list_element_t number) {
	list_t list;
	list = mentis->pool[cnt];
	list_add(list, number);
}