#include "DDeck.h"

DDeck* DDeck_init(int x, int y)
{
	DDeck* ddeck = malloc(sizeof(DDeck));

	if (ddeck)
	{
		ddeck->pos.x = x;
		ddeck->pos.y = y;

		ddeck->d = create_classic_52(2);

		frame_add_deck(ddeck);
	}

	return ddeck;
}

void DDeck_update(DDeck* ddeck)
{
	if (is_object_hovered(&ddeck->pos))
		ddeck->isHovered = true;
	else
		ddeck->isHovered = false;

	DDeck_draw(ddeck);
}

void DDeck_draw(const DDeck* ddeck)
{
	int posX = ddeck->pos.x - CW / 2;
	int posY = ddeck->pos.y - CH / 2;

	/* Draw border */
	DrawRectangle(posX - (CBOR + 2) / 2, posY - (CBOR + 2) / 2, CW + (CBOR + 2), CH + (CBOR + 2), ORANGE);

	/* Draw content */
	if (ddeck->d->size > 0)
	{
		if(ddeck->isHovered)
			DrawRectangle(posX, posY, CW, CH, LIGHTGRAY);
		else
			DrawRectangle(posX, posY, CW, CH, WHITE);
	}
	else
		DrawRectangle(posX, posY, CW, CH, ORANGE);
	
	DrawText(TextFormat("%d left", ddeck->d->size), posX + 3, posY, 10, BLACK);
	DrawText(TextFormat("D"), posX + CW / 2 - 10, posY + CH / 2 - 10, 20, BLACK);
}

void DDeck_draw_card(DDeck* ddeck)
{
	mouse_t* m = get_mouse();
	DCard_init(draw_card(ddeck->d), m->x, m->y);
}

void DDeck_destroy(DDeck* ddeck)
{
	dest_deck(ddeck->d);
	free(ddeck);
}
