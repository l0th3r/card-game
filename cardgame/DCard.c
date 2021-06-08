#include "DCard.h"
#include "DSizes.h"
#include "frame_container.h"

DCard* DCard_init(Card_t* card, int x, int y)
{
	frame_t* frame = init_frame();
	DCard* dc = NULL;

	if (!card)
		return NULL;

	dc = malloc(sizeof(DCard));

	if (dc)
	{
		dc->pos.x = x;
		dc->pos.y = y;
		dc->c = card;
		dc->isTaken = false;
		dc->isHovered = false;
		
		frame_add_card(dc);
	}

	return dc;
}

void DCard_update(DCard* dcard)
{
	if (is_object_hovered(&dcard->pos))
		dcard->isHovered = true;
	else
		dcard->isHovered = false;

	DCard_draw(dcard);
}

void DCard_draw(const DCard* dcard)
{
	int posX = dcard->pos.x - CW / 2;
	int posY = dcard->pos.y - CH / 2;

	Color clr;
	char* str = format_card_graphics(dcard->c, &clr);

	/* Draw border */
	DrawRectangle(posX - CBOR / 2, posY - CBOR / 2, CW + CBOR, CH + CBOR, clr);
	
	/* Draw content */
	DrawRectangle(posX, posY, CW, CH, WHITE);
	DrawText(TextFormat("%s", str), (posX + CW / 2) - (strlen(str) * 5), (posY + CH / 2) - 10, 20, BLACK);
}

char* format_card_graphics(const Card_t* card, Color* color)
{
	char* temp_suit;
	char* temp_pos;

	switch (card->position)
	{
	case 0:
		temp_pos = "As";
		break;
	case 10:
		temp_pos = "J";
		break;
	case 11:
		temp_pos = "Q";
		break;
	case 12:
		temp_pos = "K";
		break;
	default:
		temp_pos = TextFormat("%d", card->position + 1);
		break;
	}

	switch (card->suit)
	{
	case -1:
		temp_suit = "XX";
		*color = GRAY;
		break;
	case 0:
		temp_suit = "C";
		*color = BLACK;
		break;
	case 1:
		temp_suit = "D";
		*color = RED;
		break;
	case 2:
		temp_suit = "H";
		*color = RED;
		break;
	case 3:
		temp_suit = "S";
		*color = BLACK;
		break;
	case 4:
		temp_suit = "JO";
		temp_pos = "";
		*color = GREEN;
		break;
	default:
		temp_suit = "??";
		*color = GRAY;
		break;
	}

	return TextFormat("%s %s", temp_pos, temp_suit);
}

/*empty = -1, clubs = 0, diamonds = 1, hearts = 2, spades = 3, joker = 4 */

void DCard_destroy(DCard* dcard)
{
	dest_card(dcard->c);
	free(dcard);
}
