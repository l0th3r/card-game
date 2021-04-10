#include "../libcard.h"
#include <time.h>

void shuffle_deck(Deck_t* target)
{
    int i = 0;
    int is_good = 0;

    Deck_t* d_temp = create_deck((int)target->size, (int)target->j_nb, target->gap_start, target->gap_end);
    Card_t* c_tmp;

    /* generate seed for random */
    srand((unsigned int)time(0));

    while (i < target->size)
    {
        target->pile[i].is_used = 0;
        i++;
    }

    i = 0;
    while(i < target->size)
    {
        is_good = 0;
        while (is_good == 0)
        {
            c_tmp = get_random_card(d_temp);
            if (c_tmp->is_used == 0)
                is_good = 1;
        }
        c_tmp->is_used = target->pile[i].is_used;
        target->pile[i] = *c_tmp;
        c_tmp->is_used = 1;

        i++;
    }

    dest_deck(d_temp);
}

Card_t* get_random_card(Deck_t* src)
{
    int rnd = rand() % src->size;
    return &src->pile[rnd];
}

int rnd_nb(int cap)
{
    return rand() % cap;
}