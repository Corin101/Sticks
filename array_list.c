/* Implementacija sucelja ATP liste nizom. */

#include <stdlib.h>
#include <string.h>
#include "list.h"

#define INITIAL_CAPACITY		16

struct list_tag {
	list_element_t *values;
	int size;
	int capacity;
};

struct list_iterator_tag {
	list_t list;
	int index;
};

static void grow(list_t list);

/* public: ATP interface */

list_t list_new() {
	list_t list = malloc(sizeof(struct list_tag));
	list->values = malloc(INITIAL_CAPACITY * sizeof(list_element_t));
	list->capacity = INITIAL_CAPACITY;
	list->size = 0;
	return list;
}

void list_delete(list_t list) {
	free(list->values);
	free(list);
}

int list_is_empty(list_t list) {
	return list->size == 0;
}

int list_size(list_t list) {
	return list->size;
}

void list_add(list_t list, list_element_t elem) {
	grow(list);
	list->values[list->size] = elem;
	list->size++;
}

list_iterator_t list_iterator(list_t list) {
	list_iterator_t iter = malloc(sizeof(struct list_iterator_tag));
	iter->list = list;
	iter->index = 0;
	return iter;
}

list_iterator_t list_reverse_iterator(list_t list) {
	list_iterator_t iter = malloc(sizeof(struct list_iterator_tag));
	iter->list = list;
	iter->index = list->size - 1;
	return iter;
}

list_element_t list_get(list_iterator_t iter) {
	return iter->list->values[iter->index];
}

void list_insert(list_iterator_t iter, list_element_t elem) {
	grow(iter->list);
	memmove(iter->list->values + iter->index + 1, iter->list->values + iter->index, (iter->list->size - iter->index) * sizeof(list_element_t));
	iter->list->values[iter->index] = elem;
	iter->list->size++;
}

void list_replace(list_iterator_t iter, list_element_t elem) {
	iter->list->values[iter->index] = elem;
}

void list_remove(list_iterator_t iter) {
	memmove(iter->list->values + iter->index, iter->list->values + iter->index + 1, (iter->list->size - iter->index - 1) * sizeof(list_element_t));
	iter->list->size--;
}

void list_iterator_next(list_iterator_t iter) {
	iter->index++;
}

void list_iterator_previous(list_iterator_t iter) {
	iter->index--;
}

void list_iterator_seek(list_iterator_t iter, int n) {
	iter->index = n;
}

void list_iterator_set(list_iterator_t iter1, list_iterator_t iter2) {
	iter1->index = iter2->index;
}

int list_iterator_is_valid(list_iterator_t iter) {
	return iter->index >= 0 && iter->index < iter->list->size;
}

int list_iterator_is_equal(list_iterator_t iter1, list_iterator_t iter2) {
	return iter1->index == iter2->index;
}

void list_iterator_delete(list_iterator_t iter) {
	free(iter);
}

/* private: internals */

static void grow(list_t list) {
	if (list->size < list->capacity)
		return;
	list->capacity *= 2;
	if (!realloc(list->values, list->capacity * sizeof(list_element_t)))
		exit(-1);
}
