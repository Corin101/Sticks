#include "list.h"


struct mind {
	list_t *pool;
	unsigned pool_size;
	unsigned sticks;
	list_element_t *memory;
};
/* alociranje niza i stvaranje listi */
void allocate_pool(struct mind *mentis, unsigned pool_size);  

/* popunjava listu sa osnovnim potezima (1,2,3) */
void list_fill(list_t list,int cnt);

/*brisanje svih lista i niza*/
void delete_pool(struct mind *mentis);

/* Ucenje novih poteza nakon svake igre */
void learn_new(struct mind *mentis, int victory_status);

/* kod izgubljene igre, izbacuje los broj (ako nije zadnji) */
void mem_remove(struct mind *mentis, int cnt, list_element_t number);

/* kod pobjede, zapamti sto si odigrao */
void mem_learn(struct mind *mentis, int cnt, list_element_t number);

