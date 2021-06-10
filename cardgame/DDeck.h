#pragma once
#ifndef _D_DECK_H_
#define _D_DECK_H_

#include <raylib.h>
#include <libcard.h>

#include "DCard.h"
#include "DSizes.h"
#include "mouse_handler.h"

typedef struct
{
	Vector2 pos;
	Deck_t* d;
	bool isHovered;
	int frame_index;
} DDeck;

DDeck* DDeck_init(int x, int y);

/* draw and update ddeck */
void DDeck_update(DDeck* ddeck);

/* draw ddeck on screen */
void DDeck_draw(const DDeck* ddeck);

/* draw card from deck */
void DDeck_draw_card(DDeck* ddeck);

/* destroy deck */
void DDeck_destroy(DDeck* ddeck);

#endif