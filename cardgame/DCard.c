#include "DCard.h"
#include "mouse_handler.h"

#include <libcard.h>
#include <raylib.h>

DCard* DCard_init(Card_t* card, int x, int y)
{
	DCard* dc = NULL;

	if (!card)
		return NULL;

	dc = malloc(sizeof(DCard));

	if (dc)
	{
		dc->x = x;
		dc->y = y;
		dc->c = card;
		dc->taken = false;
	}

	return dc;
}

void update_card(DCard* dcard)
{
	mouse_t* m = get_mouse();

	if (is_card_hovered(dcard))
	{
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		if (m->left)
		{
			if (!m->holded)
				m->holded = dcard;
			else
				m->holded = NULL;
		}
	}
	else
		SetMouseCursor(MOUSE_CURSOR_ARROW);

	DCard_draw(dcard);
}

bool is_card_hovered(DCard* dcard)
{
	mouse_t* m = get_mouse();

	if (is_mouse_hovering(dcard->x - CW / 2, dcard->y - CH / 2, dcard->x + CW / 2, dcard->y + CH / 2))
		return true;
	else
		return false;
}

void DCard_draw(const DCard* dcard)
{
	int posX = dcard->x - CW / 2;
	int posY = dcard->y - CH / 2;

	Color color; /* border color */

	char* card_symbol = get_card_symbol(dcard->c);

	if (dcard->c->suit == 1 || dcard->c->suit == 2)
		color = RED;
	else if (dcard->c->suit == 4)
		color = GREEN;
	else if (dcard->c->suit == -1)
		color = GRAY;
	else
		color = BLACK;

	/* Draw border */
	DrawRectangle(posX - CBOR / 2, posY - CBOR / 2, CW + CBOR, CH + CBOR, color);
	
	/* Draw content */
	DrawRectangle(posX, posY, CW, CH, WHITE);
	DrawText(TextFormat("%s", card_symbol), (posX + CW / 2) - strlen(card_symbol) - 2, (posY + CH / 2) - 10, 20, BLACK);
}