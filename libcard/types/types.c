#include "../libcard.h"

Card_t* create_card(int id, int suit, int position)
{
	Card_t* card = malloc(sizeof(Card_t));

	if (!card)
		return NULL;

	card->id = id;
	card->suit = suit;
	card->position = position;
	card->hidden = 0;
	card->is_used = 0;

	return card;
}

Deck_t* create_deck(int length, int joker_len, int gap_start, int gap_end)
{
	int i = 0;
	int j = 0;
	int k = 0;

	Deck_t *deck = malloc(sizeof(Deck_t));

	if(deck)
	{
		/* allocate the pile */
		deck->pile = create_list_Card_t();

		if(deck->pile)
		{
			/* create cards */
			/* loop through suits */
			while(j < 4)
			{	
				/* loop through each suit */
				k = 0;
				while(k < 13)
				{
					/* only if the card is not in the gap */
					if(k < gap_start - 1 || k > gap_end - 1)
					{
						list_Card_t_add(deck->pile, create_card(i, j, k));
						i++;
					}
					k++;
				}
				j++;
			}

			/* create joker cards */
			j = 0;
			while(j < joker_len)
			{
				list_Card_t_add(deck->pile, create_card(i, 4, j));
				j++;
				i++;
			}
			deck->gap_start = gap_start;
			deck->gap_end = gap_end;
		}

		deck->size = (size_t)length + joker_len;
		deck->j_nb = joker_len;
	}
	return deck;
}

Deck_t* create_classic_52(int joker_amount)
{
	return create_deck(52, joker_amount, 14, -1);
}

Deck_t* create_classic_32(int joker_amount)
{
	return create_deck(32, joker_amount, 2, 6);
}

void dest_deck(Deck_t* target)
{
	destroy_list_Card_t(target->pile);
	free(target);
}

void dest_card(Card_t* target)
{
	free(target);
}

LIST_DEFINE(Card_t);