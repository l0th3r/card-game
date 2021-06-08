#include "frame_container.h"

frame_t* init_frame()
{
	static frame_t* frame = NULL;

	if (!frame)
	{
		frame = malloc(sizeof(frame_t));
		if (frame)
		{
			frame->can_move_cards = true;
			frame->can_move_decks = false;
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

	draw_frame_decks();
	draw_frame_cards();

	update_frame_cards();
	update_frame_decks();

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
		if (dcard->isHovered && frame->can_move_cards)
			frame->is_hovering = true;

		if (!mouse->holded && mouse->left_p && dcard->isHovered && frame->can_move_cards && frame->can_click_this_frame)
		{
			frame_select_card(dcard, index);
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

		if (!mouse->holded && mouse->left && ddeck->isHovered && frame->can_move_decks && frame->can_click_this_frame)
		{
			grab_object(&ddeck->pos);
			frame->can_click_this_frame = false;
		}
		else if (!mouse->holded && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && ddeck->isHovered)
			DDeck_draw_card(ddeck);
	});
}

void frame_select_card(DCard* dcard, int index)
{
	frame_t* frame = init_frame();

	list_DCard_remove(frame->cards, index);
	list_DCard_add(frame->cards, dcard);
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