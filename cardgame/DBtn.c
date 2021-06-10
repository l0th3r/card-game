#include "DBtn.h"
#include <stdlib.h>
#include <stdio.h>

#include "DDeck.h"
#include "DDisc.h"
#include "DSizes.h"

DBtn* DBtn_init(btn_type type, const char* content, Color color, int x, int y)
{
	DBtn* dbtn = malloc(sizeof(DBtn));

	if (dbtn)
	{
		dbtn->pos.x = x;
		dbtn->pos.y = y;

		dbtn->type = type;

		dbtn->color = color;
		dbtn->text = content;

		dbtn->isHovered = false;
		dbtn->frame_index = 0;
		frame_add_dbtn(dbtn);
	}

	return dbtn;
}

void DBtn_update(DBtn* dbtn)
{
	mouse_t* mouse = get_mouse();
	dbtn->isHovered = is_mouse_hovering(dbtn->pos.x - BW / 2, dbtn->pos.y - BH / 2, dbtn->pos.x + BW / 2, dbtn->pos.y + BH / 2);

	DBtn_draw(dbtn);
}

void DBtn_draw(const DBtn* dbtn)
{
	int posX = dbtn->pos.x - BW / 2;
	int posY = dbtn->pos.y - BH / 2;

	/* Draw border */
	DrawRectangle(posX - (CBOR + 2) / 2, posY - (CBOR + 2) / 2, BW + (CBOR + 2), BH + (CBOR + 2), dbtn->color);

	/* Draw content */
	if (dbtn->isHovered)
		DrawRectangle(posX, posY, BW, BH, dbtn->color);
	else
		DrawRectangle(posX, posY, BW, BH, WHITE);

	DrawText(dbtn->text, posX + 10, posY + BH / 2 - 3, 10, BLACK);
}

void DBtn_event(const DBtn* dbtn)
{
	mouse_t* mouse = get_mouse();

	switch (dbtn->type)
	{
	case BTN_ADD_DECK:
		DDeck_init(mouse->x, mouse->y);
		break;
	case BTN_ADD_DISC:
		DDisc_init(mouse->x, mouse->y);
	}
}

void DBtn_destroy(DBtn* dbtn)
{
	free(dbtn);
}