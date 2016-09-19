#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "game.h"
#include "config.h"
#include "string.h"

int player_turn (struct mind *mentis) {
	int result;
	while(1) {
		scanf("%d",&result);
		if (result > mentis->sticks) {
			printf("\nWrong input, not enough sticks, try again");
			continue;
		}
		if (result > 0 && result < 4)
			break;
		printf("\nWrong input, you may pick between 1 - 3 sticks");
		game_status(mentis,1);
		continue;
	}
	mentis->sticks -= result;
	return mentis->sticks > 0?0:1;
}

int comp_turn(struct mind *mentis) {
	list_element_t result;
	list_t list;
	list_iterator_t iter;

	list = mentis->pool[mentis->sticks-1];
	
	iter = list_iterator(list);
	list_iterator_seek(iter,rand() % list_size(list));
	result = list_get(iter);
	printf("%d",result);
	mentis->memory[mentis->sticks-1] = result;
	mentis->sticks -= result;

	list_iterator_delete(iter);
	if (mentis->sticks == 0)
		return 1;
	return 0;
}

int stick_checkup(struct mind *mentis) {
	if (mentis->sticks == 2) {
		printf("%d",1);
		mentis->sticks -= 1;
		return 1;
	}
	if (mentis->sticks == 3) {
		printf("%d",2);
		mentis->sticks -= 2;
		return 1;
	}

	printf("%d",1);
	mentis->sticks -= 1;
	return 0;
}
void game_status(struct mind *mentis,int player) {
	if (player == 1)
		putchar('\n');
	printf("\nSticks left in the game:: %d\n",mentis->sticks);
	printf("Player %d:: How many sticks do you want to take? (1-3):: ",player);
}

void save_game(struct mind *mentis) {
	FILE *dat;
	char buffer[50];
	while(1) {
		printf("\nType the name of file you wish to use for saving my progress, ");
		printf("\nPlease also include the extension of file:: ");
		scanf("%s",buffer);
		dat = fopen(buffer,"w");
		if (dat == NULL) {
			printf("Could not open/create the file named %s", buffer);
			continue;
		}
		break;
	}
	save_everything(mentis, dat);
	fclose(dat);
}

void save_everything(struct mind *mentis, FILE *file) {
	list_t list;
	list_iterator_t iter;
	int cnt=0;
	while(cnt != mentis->pool_size) {
		fprintf(file,"%d ",cnt+1);
		list = mentis->pool[cnt];
		for(iter = list_iterator(list);list_iterator_is_valid(iter);list_iterator_next(iter))	
			fprintf(file,"%d ",list_get(iter));
		fprintf(file,"\n");
		++cnt;
	}
}

void load_game(struct mind *mentis,int pool_size) {
	char buffer[50];
	FILE *file;
	int cnt;
	while(1) {
		printf("Do you wish the load your previous progress? yes or no?");
		scanf("%s",buffer);
		if (strcmp(buffer,"yes"))
			return;
		printf("\nType the path to the file you wish to load,");
		printf("\nPlease also include the extension of file:: ");
		scanf("%s",buffer);
		file = fopen(buffer,"r");
		if (file == NULL) {
			printf("\nCould not open the file %s",buffer);
			continue;
		}
		break;
	}

	mentis->pool_size = pool_size;
	mentis->sticks = 0;
	mentis->pool = malloc(sizeof(list_t) * mentis->pool_size);
	mentis->memory = calloc(mentis->pool_size, sizeof(list_element_t));
	for(cnt=0;cnt != pool_size;++cnt) {
		mentis->pool[cnt] = list_new();
		insert_list(mentis->pool[cnt], file);
	}
}

void insert_list(list_t list, FILE *file) {
	int buffer;
	buffer = fgetc(file);
	for(;;) {
		buffer = fgetc(file);
		if (buffer == '\n')
			return;
		if (buffer != '1' && buffer != '2' && buffer != '3')
			continue;
		list_add(list,buffer - '0');
	}
}