#include "list.h"

/* potez igraca, vraca 0 ako nema vise stickova, 1 inace */
int player_turn (struct mind *mentis);

/* potez racunala, vraca 0 ako nema vise stickova, 1 inace */
int comp_turn(struct mind *mentis);

/* provjerava da nema 4 ili manje sticks i radi odgovarajuci potez */
int stick_checkup(struct mind *mentis);

/*game status (ispis koji igrac je na potezu i broj stickova*/
void game_status(struct mind *mentis,int player);

/* sacuva trenutno stanje lista u .txt file */
void save_game(struct mind *mentis);

/* prebacivanje lista u datoteku */
void save_everything(struct mind *mentis, FILE *file);

/* ucitavanje sacuvanog napretka iz datoteke */
void load_game(struct mind *mentis, int pool_size);

/* ubacuje podatke iz datoteke u listu */
void insert_list(list_t list, FILE *file);