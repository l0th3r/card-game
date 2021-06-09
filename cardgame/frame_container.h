#pragma once
#ifndef _FRAME_CONTAINER_
#define _FRAME_CONTAINER_

#include <list_generic.h>
#include "foreach.h"

#include "DCard.h"
#include "DDeck.h"
#include "DSlot.h"
#include "DDisc.h"

LIST_DECLARE(DDisc);
LIST_DECLARE(DCard);
LIST_DECLARE(DDeck);

typedef struct
{
	DCard* holded_card;

	bool can_move_cards;
	bool can_move_decks;
	bool can_move_discs;
	bool can_move_slots;

	bool is_hovering;
	bool can_click_this_frame;

	list_DCard* cards;
	list_DDeck* decks;
	list_DDisc* discs;
} frame_t;

/* create or get frame struct */
frame_t* init_frame();

/* update all the game content (need to be drawned) */
void update_frame();

/* select the targetted card */
void frame_select_card(DCard* dcard);
/* unselect the current selected card */
void frame_unselect_card();

/* draw frame */
void draw_frame_cards();
void draw_frame_decks();
void draw_frame_discs();

/* update frame */
void update_frame_cards();
void update_frame_decks();
void update_frame_discs();

/* add to frame */
void frame_add_card(DCard* dcard);
void frame_add_deck(DDeck* ddeck);
void frame_add_disc(DDisc* ddisc);

/* destroy all cards */
void dest_frame();

#endif