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
			frame->can_move_decks = false;
			frame->can_move_discs = false;
			frame->can_move_slots = false;

			frame->is_hovering = false;
			frame->can_click_this_frame = true;

			frame->cards = create_list_DCard();
			frame->decks = create_list_DDeck();
			frame->discs = create_list_DDisc();
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

	draw_frame_discs();
	draw_frame_decks();
	draw_frame_cards();

	update_frame_cards();
	update_frame_decks();
	update_frame_discs();

	if (mouse->holded && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		mouse_release();

	/* change cursor if something is hovered */
	if (frame->is_hovering)
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	else
		SetMouseCursor(MOUSE_CURSOR_ARROW);
}

void draw_frame_cards()
{
	frame_t* frame = init_frame();

	/* UPDATE THE Card */
	FOREACH_LIST(DCard, dcard, frame->cards->_list, { DCard_update(dcard); });
}

void draw_frame_decks()
{
	frame_t* frame = init_frame();

	/* UPDATE THE DRAW ON DECK */
	FOREACH_LIST(DDeck, ddeck, frame->decks->_list, { DDeck_update(ddeck); });
}

void draw_frame_discs()
{
	frame_t* frame = init_frame();

	/* UPDATE THE DRAW ON DECK */
	FOREACH_LIST(DDisc, ddisc, frame->discs->_list, { DDisc_update(ddisc); });
}

void update_frame_cards()
{
	frame_t* frame = init_frame();
	mouse_t* mouse = get_mouse();

	int index = frame->cards->_list->count - 1;

	/* 
		UPDATE THE CLICK ON CARDS 
		Update the click on reverse to always privilege the deck drawed on top
	*/
	FOREACH_LIST_REVERSE(DCard, dcard, frame->cards->_list,
	{
		dcard->frame_index = index;

		if (dcard->isHovered && frame->can_move_cards)
			frame->is_hovering = true;

		if (!mouse->holded && mouse->left_p && dcard->isHovered && frame->can_move_cards && frame->can_click_this_frame)
		{
			frame_select_card(dcard);
			grab_object(&dcard->pos);
			frame->can_click_this_frame = false;
		}

		index--;
	});
}

void update_frame_decks()
{
	frame_t* frame = init_frame();
	mouse_t* mouse = get_mouse();

	/*
		UPDATE THE CLICK ON DECKS
		Update the click on reverse to always privilege the deck drawed on top
	*/
	FOREACH_LIST_REVERSE(DDeck, ddeck, frame->decks->_list,
	{
		if (ddeck->isHovered)
			frame->is_hovering = true;

		if (!mouse->holded && mouse->left_p && ddeck->isHovered && frame->can_move_decks && frame->can_click_this_frame)
		{
			grab_object(&ddeck->pos);
			frame->can_click_this_frame = false;
		}
		else if (!mouse->holded && mouse->left_p && ddeck->isHovered)
			DDeck_draw_card(ddeck);
	});
}

void update_frame_discs()
{
	frame_t* frame = init_frame();
	mouse_t* mouse = get_mouse();

	/*
		UPDATE THE CLICK ON DECKS
		Update the click on reverse to always privilege the deck drawed on top
	*/
	FOREACH_LIST_REVERSE(DDisc, ddisc, frame->discs->_list,
	{
		if (ddisc->isHovered)
			frame->is_hovering = true;

		if (!mouse->holded && mouse->left && ddisc->isHovered && frame->can_move_discs && frame->can_click_this_frame)
		{
			grab_object(&ddisc->pos);
			frame->can_click_this_frame = false;
		}
		else if (ddisc->isHovered && frame->holded_card && mouse->left_r)
		{
			list_DCard_remove(frame->cards, frame->holded_card->frame_index);
			DDisc_add_card(ddisc, frame->holded_card);
			frame_unselect_card();
		}
	});
}

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

void frame_add_card(DCard* dcard)
{
	frame_t* frame = init_frame();
	list_DCard_add(frame->cards, dcard);
}

void frame_add_deck(DDeck* ddeck)
{
	frame_t* frame = init_frame();
	list_DDeck_add(frame->decks, ddeck);
}

void frame_add_disc(DDisc* ddisc)
{
	frame_t* frame = init_frame();
	list_DDisc_add(frame->discs, ddisc);
}

void dest_frame()
{
	frame_t* frame = init_frame();

	FOREACH_LIST(DCard, dcard, frame->cards->_list, { DCard_destroy(dcard); });
	FOREACH_LIST(DDeck, ddeck, frame->decks->_list, { DDeck_destroy(ddeck); });
	FOREACH_LIST(DDisc, ddisc, frame->discs->_list, { DDisc_destroy(ddisc); });

	destroy_list_DCard(frame->cards);
	destroy_list_DDeck(frame->decks);
	destroy_list_DDisc(frame->discs);

	free(frame);
}

LIST_DEFINE(DCard);
LIST_DEFINE(DDeck);
LIST_DEFINE(DDisc);