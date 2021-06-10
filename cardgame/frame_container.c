#include "frame_container.h"

frame_t* init_frame()
{
	static frame_t* frame = NULL;

	if (!frame)
	{
		frame = malloc(sizeof(frame_t));
		if (frame)
		{
			frame->holded_card = NULL;

			frame->can_move_cards = true;
			frame->can_move_decks = true;
			frame->can_move_discs = true;
			frame->can_move_dbtns = true;

			frame->is_hovering = false;
			frame->can_click_this_frame = true;

			frame->plate = NULL;

			frame->cards = create_list_DCard();
			frame->decks = create_list_DDeck();
			frame->discs = create_list_DDisc();
			frame->dbtns = create_list_DBtn();
		}
	}
	return(frame);
}

void update_frame()
{
	frame_t* frame = init_frame();
	mouse_t* mouse = get_mouse();

	frame->is_hovering = false;
	frame->can_click_this_frame = true;

	if(frame->plate)
		DPlate_update(frame->plate);

	draw_frame_dbtn();
	draw_frame_ddisc();
	draw_frame_ddeck();
	draw_frame_dcard();

	update_frame_dcard();
	update_frame_ddeck();
	update_frame_ddisc();
	update_frame_dbtn();
	
	if (mouse->right_r)
	{
		mouse_release();
		frame->holded_card = NULL;
	}

	/* change cursor if something is hovered */
	if (mouse->holded)
		SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
	else if (frame->is_hovering)
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	else
		SetMouseCursor(MOUSE_CURSOR_ARROW);

	DrawText(TextFormat("Right click to move elements (all of them)"), 10, 5, 20, BLACK);
	DrawText(TextFormat("Left click to interact with elements"), 10, 30, 20, BLACK);
}

UPDATE_FRAME_DEFN(DCard, dcard, cards,
{
	frame_select_card(dcard);
}, {}, {});

UPDATE_FRAME_DEFN(DDeck, ddeck, decks,
{},
{
	DDeck_draw_card(ddeck);
}, {});

UPDATE_FRAME_DEFN(DDisc, ddisc, discs,
{}, {},
{
	if (ddisc->isHovered && frame->holded_card && mouse->right_r)
	{
		list_DCard_remove(frame->cards, frame->holded_card->frame_index);
		DDisc_add_card(ddisc, frame->holded_card);
		frame_unselect_card();
	}
});

UPDATE_FRAME_DEFN(DBtn, dbtn, dbtns,
{},
{
	DBtn_event(dbtn);
}, {});

void frame_select_card(DCard* dcard)
{
	frame_t* frame = init_frame();

	list_DCard_remove(frame->cards, dcard->frame_index);
	list_DCard_add(frame->cards, dcard);

	frame->holded_card = dcard;
}

void frame_unselect_card()
{
	frame_t* frame = init_frame();
	frame->holded_card = NULL;
}

void frame_add_plate(const DPlate* dplate)
{
	frame_t* frame = init_frame();
	if (!frame->plate)
		frame->plate = dplate;
}

void place_in_plate(Vector2* coord)
{
	frame_t* frame = init_frame();

	if (frame->plate)
	{
		/* x */
		while (!DPlate_compare_x(frame->plate, coord->x))
		{
			if (coord->x < frame->plate->pos.x)
				coord->x += 10;
			else
				coord->x -= 10;
		}

		/* y */
		while (!DPlate_compare_y(frame->plate, coord->y))
		{
			if (coord->y < frame->plate->pos.y)
				coord->y += 10;
			else
				coord->y -= 10;
		}
	}
}

void dest_frame()
{
	frame_t* frame = init_frame();

	FOREACH_LIST(DCard, dcard, frame->cards->_list, { DCard_destroy(dcard); });
	FOREACH_LIST(DDeck, ddeck, frame->decks->_list, { DDeck_destroy(ddeck); });
	FOREACH_LIST(DDisc, ddisc, frame->discs->_list, { DDisc_destroy(ddisc); });
	FOREACH_LIST(DBtn, dbtn, frame->dbtns->_list, { DBtn_destroy(dbtn); });

	destroy_list_DCard(frame->cards);
	destroy_list_DDeck(frame->decks);
	destroy_list_DDisc(frame->discs);
	destroy_list_DBtn(frame->dbtns);

	DPlate_destroy(frame->plate);

	free(frame);
}

DRAW_FRAME_DEFN(DCard, dcard, cards);
DRAW_FRAME_DEFN(DDeck, ddeck, decks);
DRAW_FRAME_DEFN(DDisc, ddisc, discs);
DRAW_FRAME_DEFN(DBtn, dbtn, dbtns);

FRAME_ADD_DEFN(DCard, dcard, cards);
FRAME_ADD_DEFN(DDeck, ddeck, decks);
FRAME_ADD_DEFN(DDisc, ddisc, discs);
FRAME_ADD_DEFN(DBtn, dbtn, dbtns);

LIST_DEFINE(DCard);
LIST_DEFINE(DDeck);
LIST_DEFINE(DDisc);
LIST_DEFINE(DBtn);
