#pragma once
#ifndef _FRAME_CONTAINER_
#define _FRAME_CONTAINER_

#include <list_generic.h>
#include "foreach.h"

#include "DCard.h"
#include "DDeck.h"

LIST_DECLARE(DDeck);
LIST_DECLARE(DCard);

typedef struct
{
	bool can_move_cards;
	bool can_move_decks;
	bool can_move_slots;

	bool is_hovering;

	list_DCard* cards;
	list_DDeck* decks;
} frame_t;

/* create or get frame struct */
frame_t* init_frame();

/* update all the game content (need to be drawned) */
void update_frame();

/* add card to frame */
void frame_add_card(DCard* dcard);

/* destroy all cards */
void dest_frame();

#endif