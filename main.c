#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "list.h"
#include "config.h"

int main() {
	int result, victory_status;
	int pool_size = 10;
	struct mind *mentis;

	srand((unsigned) time(NULL));
	mentis = malloc(sizeof(struct mind));

	load_game(mentis,pool_size);

	while(1) {

	allocate_pool(mentis,pool_size);

		while(1) {
			game_status(mentis,1);
			if (player_turn(mentis)) {
				victory_status = 1;
				break;
			}
			game_status(mentis,2);
			if (comp_turn(mentis)) {
				victory_status = 0;
				break;
			}
		}

		learn_new(mentis, victory_status);
		printf("\nGame Over");
		printf("\nWant to play another game? Type 1 if yes, 0 otherwise ");
		scanf("%d",&result);
		if (!result)
			break;
		system("cls");
	}
	save_game(mentis);

	printf("bye");
	delete_pool(mentis);

	return 0;
}
