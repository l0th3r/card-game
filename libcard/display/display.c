#include "../libcard.h"

#define STD 5
#define STRV 5
#define STR 15

char* get_card_symbol(Card_t* target)
{
	int suit = target->suit;
	int pos = target->position;
	int hidden = target->hidden;

	char* suit_to_display = malloc(sizeof(char) * STD);
	char* str_val = malloc(sizeof(char) * STRV);
	char* str = malloc(sizeof(char) * STR);

	/* set suit to display */
	switch (suit)
	{
	case 0:
		strcpy(suit_to_display, "♣"); /* ♣ */
		break;
	case 1:
		strcpy(suit_to_display, "♦"); /* ♦ */
		break;
	case 2:
		strcpy(suit_to_display, "♥"); /* ♥ */
		break;
	case 3:
		strcpy(suit_to_display, "♠"); /* ♠ */
		break;
	}

	/* set card to display */
	switch (pos)
	{
	case 0:
		strcpy(str_val, "As");
		break;
	case 9:
		snprintf(str_val, STRV,"%d", pos + 1);
		break;
	case 10:
		strcpy(str_val, "J ");
		break;
	case 11:
		strcpy(str_val, "Q ");
		break;
	case 12:
		strcpy(str_val, "K ");
		break;
	default:
		snprintf(str_val, STRV, "%d ", pos + 1);
		break;
	}

	if (hidden == 1)
		snprintf(str, STR, "??");
	else if (suit == -1)
		snprintf(str, STR, "  ");
	else if (suit == 4)
		snprintf(str, STR, "JO");
	else
		snprintf(str, STR, "%s%s", suit_to_display, str_val);

	free(str_val);
	free(suit_to_display);

	return str;
}

char* get_card_name(Card_t* target)
{
	int suit = target->suit;
	int pos = target->position;
	int hidden = target->hidden;

	char suit_to_display[10];
	char str_val[10];
	char str[25];

	/* set suit to display */
	switch(suit)
	{
		case 0:
			strcpy(suit_to_display, "Club");
			break;
		case 1:
			strcpy(suit_to_display, "Diamond");
			break;
		case 2:
			strcpy(suit_to_display, "Heart");
			break;
		case 3:
			strcpy(suit_to_display, "Spade");
			break;
	}

	/* set card to display */
	switch (pos)
	{
		case 0:
			strcpy(str_val, "As");
			break;
		case 10:
			strcpy(str_val, "Jack");
			break;
		case 11:
			strcpy(str_val, "Queen");
			break;
		case 12:
			strcpy(str_val, "King");
			break;
		default:
			sprintf(str_val, "%d", pos + 1);
			break;
	}

	if(hidden == 1)
		sprintf(str, "Hidden Card");
	else if(suit == 4)
		sprintf(str, "Joker");
	else if(suit == -1)
		sprintf(str, "Empty card");
	else
		sprintf(str, "%s of %s", str_val, suit_to_display);

	return str;
}