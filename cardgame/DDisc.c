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
	}

	return ddisc;
}

void DDisc_update(DDisc* ddisc)
{
	if (is_object_hovered(&ddisc->pos))
		ddisc->isHovered = true;
	else
		ddisc->isHovered = false;

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
	DrawRectangle(posX, posY, CW, CH, WHITE);

	DrawText(TextFormat("%d left", ddisc->pile->_list->count), posX, posY, 10, BLACK);
	DrawText(TextFormat("XX"), posX + CW / 2 - 10, posY + CH / 2 - 10, 20, BLACK);
}

void DDisc_destroy(DDisc* ddisc)
{
	destroy_list_Card_t(ddisc->pile);
	free(ddisc);
}