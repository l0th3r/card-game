#pragma once
#ifndef _FRAME_CONTAINER_
#define _FRAME_CONTAINER_

#include <list_generic.h>
#include "foreach.h"
#include "frame_func_format.h"

#include "DCard.h"
#include "DDeck.h"
#include "DBtn.h"
#include "DDisc.h"
#include "DPlate.h"

LIST_DECLARE(DDisc);
LIST_DECLARE(DCard);
LIST_DECLARE(DDeck);
LIST_DECLARE(DBtn);

FRAME_FUNC_DECL(DCard, dcard, cards);
FRAME_FUNC_DECL(DDeck, ddeck, decks);
FRAME_FUNC_DECL(DDisc, ddisc, discs);
FRAME_FUNC_DECL(DBtn, dbtn, dbtns);

typedef struct
{
	DCard* holded_card;

	bool can_move_cards;
	bool can_move_decks;
	bool can_move_discs;
	bool can_move_dbtns;

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

/* add the plate to frame */
void frame_add_plate(const DPlate* dplate);

/* destroy all cards */
void dest_frame();

#endif