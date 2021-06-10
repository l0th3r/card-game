#pragma once
#ifndef _FRAME_CONTAINER_
#define _FRAME_CONTAINER_

#include <list_generic.h>
#include "foreach.h"

#include "DCard.h"
#include "DDeck.h"
#include "DBtn.h"
#include "DDisc.h"
#include "DPlate.h"

LIST_DECLARE(DDisc);
LIST_DECLARE(DCard);
LIST_DECLARE(DDeck);
LIST_DECLARE(DBtn);

typedef struct
{
	DCard* holded_card;

	bool can_move_cards;
	bool can_move_decks;
	bool can_move_discs;
	bool can_move_btns;

	bool is_hovering;
	bool can_click_this_frame;

	DPlate* plate;

	list_DCard* cards;
	list_DDeck* decks;
	list_DDisc* discs;
	list_DBtn*	dbtns;
} frame_t;

/* create or get frame struct */
frame_t* init_frame();

/* update all the game content (need to be drawned) */
void update_frame();

/* select the targetted card */
void frame_select_card(DCard* dcard);

/* unselect the current selected card */
void frame_unselect_card();

/* move an element until it is in the plate (pass its position as a parameter) */
void place_in_plate(Vector2* coord);

/* draw frame */
void draw_frame_cards();
void draw_frame_decks();
void draw_frame_discs();
void draw_frame_btns();

/* update frame */
void update_frame_cards();
void update_frame_decks();
void update_frame_discs();
void update_frame_btns();

/* add to frame */
void frame_add_card(const DCard* dcard);
void frame_add_deck(const DDeck* ddeck);
void frame_add_disc(const DDisc* ddisc);
void frame_add_btn(const DBtn* dbtn);
void frame_add_plate(const DPlate* dplate);

/* destroy all cards */
void dest_frame();

#endif