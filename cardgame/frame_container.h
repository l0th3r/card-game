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
void frame_select_card(DCard* dcard, int index);

/* draw frame cards */
void draw_frame_cards();

/* draw frame decks */
void draw_frame_decks();

/* update frame cards */
void update_frame_cards();

/* update frame decks */
void update_frame_decks();

/* add card to frame */
void frame_add_card(DCard* dcard);

/* add deck to frame*/
void frame_add_deck(DDeck* ddeck);

/* destroy all cards */
void dest_frame();

#endif