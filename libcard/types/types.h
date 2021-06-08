#ifndef CARD_TYPES
#define CARD_TYPES

typedef struct
{	
	/* position in the deck */
	int id;

	/*empty = -1, clubs = 0, diamonds = 1, hearts = 2, spades = 3, joker = 4 */
	int suit;

	/* position of the card on the suit from 0 to 12 (0 is As 12 is king) */
	int position;
	
	/* 1 if the card should be hidden */
	int hidden;

	/* 1 if the card is used else 0 */
	int is_used;
} Card_t;

LIST_DECLARE(Card_t);

typedef struct
{
	list_Card_t* pile;
	size_t size;
	size_t j_nb;
	int gap_start;
	int gap_end;
} Deck_t;

/* allocate */
Card_t* create_card(int id, int suit, int position);
Deck_t* create_deck(int length, int joker_len, int gap_start, int gap_end);
Deck_t* create_classic_52(int joker_amount);
Deck_t* create_classic_32(int joker_amount);

/* destroy */
void dest_deck(Deck_t* target);
void dest_card(Card_t* target);

#endif