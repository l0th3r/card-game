#pragma once
#ifndef _D_DISC_H_
#define _D_DISC_H_

#include <raylib.h>
#include <libcard.h>

#include "DCard.h"
#include "DSizes.h"
#include "mouse_handler.h"

typedef struct
{
	Vector2 pos;
	list_Card_t* pile;
	bool isHovered;
	int frame_index;
} DDisc;

DDisc* DDisc_init(int x, int y);

/* draw and update ddisc */
void DDisc_update(DDisc* ddisc);

/* draw ddeck on screen */
void DDisc_draw(const DDisc* ddisc);

/* add card to discard pile */
void DDisc_add_card(DDisc* ddisc, DCard* dcard);

/* destroy deck */
void DDisc_destroy(DDisc* ddisc);

#endif