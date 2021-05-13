#pragma once
#ifndef _D_DECK_H_
#define _D_DECK_H_

#include <raylib.h>
#include <libcard.h>

#include "DCard.h"
#include "DSizes.h"
#include "mouse_handler.h"
#include "frame_container.h"

typedef struct
{
	Vector2 pos;
	DCard* top;
	Deck_t* d;
	bool isHidden;
} DDeck;

DDeck* DDeck_init(Deck_t* deck, bool isHidden, int x, int y);

#endif