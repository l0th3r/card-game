#include "DDisc.h"

DDisc* DDisc_init(int x, int y)
{
	DDisc* ddisc = malloc(sizeof(ddisc));

	if (ddisc)
	{
		ddisc->pos.x = x;
		ddisc->pos.y = y;
		ddisc->pile = create_list_Card_t();

		ddisc->isHovered = false;
		ddisc->frame_index = -1;
		frame_add_ddisc(ddisc);
	}

	return ddisc;
}

void DDisc_update(DDisc* ddisc)
{
	ddisc->isHovered = is_object_hovered(&ddisc->pos);
	DDisc_draw(ddisc);
}

void DDisc_draw(const DDisc* ddisc)
{
	int posX = ddisc->pos.x - CW / 2;
	int posY = ddisc->pos.y - CH / 2;

	Color color; /* border color */

	/* Draw border */
	DrawRectangle(posX - (CBOR + 2) / 2, posY - (CBOR + 2) / 2, CW + (CBOR + 2), CH + (CBOR + 2), DARKGRAY);

	/* Draw content */
	if(ddisc->isHovered)
		DrawRectangle(posX, posY, CW, CH, DARKGRAY);
	else
		DrawRectangle(posX, posY, CW, CH, WHITE);

	DrawText(TextFormat("%d cards", ddisc->pile->_list->count), posX + 3, posY, 10, BLACK);
	DrawText(TextFormat("Discard"), posX + 5, posY + CH / 2 - 10, 10, BLACK);
}

void DDisc_add_card(DDisc* ddisc, DCard* dcard)
{
	list_Card_t_add(ddisc->pile, dcard->c);
	free(dcard);
}

void DDisc_destroy(DDisc* ddisc)
{
	destroy_list_Card_t(ddisc->pile);
}