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

			frame->cards = create_list_DCard();
			frame->decks = create_list_DDeck();
		}
	}
	return(frame);
}

void update_frame()
{
	frame_t* frame = init_frame();
	mouse_t* mouse = get_mouse();

	frame->is_hovering = false;
	FOREACH_LIST(DCard, dcard, frame->cards->_list,
	{
		update_card(dcard);
		
		if (dcard->isHovered && frame->can_move_cards)
			frame->is_hovering = true;

		if (!mouse->holded && mouse->left && dcard->isHovered && frame->can_move_cards)
			give_card(&dcard->pos);
	});

	if (mouse->holded && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		mouse->holded = NULL;

	/* change cursor if something is hovered */
	if (frame->is_hovering)
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	else
		SetMouseCursor(MOUSE_CURSOR_ARROW);
}

void frame_add_card(DCard* dcard)
{
	frame_t* frame = init_frame();
	list_DCard_add(frame->cards, dcard);
}

void dest_frame()
{
	frame_t* f = init_frame();

	destroy_list_DCard(f->cards);
	destroy_list_DDeck(f->decks);

	free(f);
}

LIST_DEFINE(DCard);
LIST_DEFINE(DDeck);