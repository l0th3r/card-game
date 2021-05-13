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

void update_card(DCard* dcard)
{
	mouse_t* m = get_mouse();

	if (is_card_hovered(dcard))
		dcard->isHovered = true;
	else
		dcard->isHovered = false;

	DCard_draw(dcard);
}

bool is_card_hovered(DCard* dcard)
{
	mouse_t* m = get_mouse();

	if (is_mouse_hovering(dcard->pos.x - CW / 2, dcard->pos.y - CH / 2, dcard->pos.x + CW / 2, dcard->pos.y + CH / 2))
		return true;
	else
		return false;
}

void DCard_draw(const DCard* dcard)
{
	int posX = dcard->pos.x - CW / 2;
	int posY = dcard->pos.y - CH / 2;

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