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
        Card_t* temp = list_Card_t_get(target->pile, i);
        temp->is_used = 0;
        i++;
    }

    i = 0;
    while(i < target->size)
    {
        is_good = 0;
        while (is_good == 0)
        {
            c_tmp = list_Card_t_get(target->pile, get_random_card(target));
            if (c_tmp->is_used == 0)
                is_good = 1;
        }
        c_tmp = list_Card_t_get(target->pile, i);
        c_tmp->is_used = 1;

        i++;
    }

    dest_deck(d_temp);
}

int get_random_card(Deck_t* src)
{
    int rnd = rand() % src->size;
    return rnd;
}

Card_t* draw_card(Deck_t* src)
{
    int idx = 0;
    if (src->size >= 1)
    {
        idx = get_random_card(src);
        Card_t* temp = list_Card_t_get(src->pile, idx);
        list_Card_t_remove(src->pile, idx);
        src->size -= 1;
        return temp;
    }
    else
        return NULL;
}

int rnd_nb(int cap)
{
    return rand() % cap;
}