#pragma once
#ifndef _FRAME_FUNC_FORMAT_
#define _FRAME_FUNC_FORMAT_

/* DECL */
#define DRAW_FRAME_DECL(TYPE, KEYWORD, FRAMENAME)\
	void draw_frame_##KEYWORD();

#define UPDATE_FRAME_DECL(TYPE, KEYWORD, FRAMENAME)\
	void update_frame_##KEYWORD();

#define FRAME_ADD_DECL(TYPE, KEYWORD, FRAMENAME)\
	void frame_add_##KEYWORD();

/* DEFN */
#define DRAW_FRAME_DEFN(TYPE, KEYWORD, FRAMENAME)\
	void draw_frame_##KEYWORD() {\
		frame_t* frame = init_frame();\
		FOREACH_LIST(TYPE, KEYWORD, frame->##FRAMENAME##->_list, { TYPE##_update(KEYWORD); });}

/*
	MOVE_CODE		the code to execute when the object is moving
	INTERACT_CODE	the code to execute when the object is clicked
	EXTENT_CODE		the code to exectute after previous actions
*/
#define UPDATE_FRAME_DEFN(TYPE, KEYWORD, FRAMENAME, MOVE_CODE, INTERACT_CODE, EXTEND_CODE)\
	void update_frame_##KEYWORD(){\
		frame_t* frame = init_frame(); mouse_t* mouse = get_mouse();\
		int index = frame->##FRAMENAME##->_list->count - 1;\
		FOREACH_LIST_REVERSE(TYPE, KEYWORD, frame->##FRAMENAME##->_list, {\
			KEYWORD##->frame_index = index; if (KEYWORD##->isHovered && frame->can_move_##FRAMENAME) frame->is_hovering = true;\
			if (mouse->right_p && !mouse->holded && KEYWORD##->isHovered && frame->can_move_##FRAMENAME && frame->can_click_this_frame)\
				{ {MOVE_CODE;} grab_object(&##KEYWORD##->pos); frame->can_click_this_frame = false;}\
			else if (!mouse->holded && mouse->left_p && KEYWORD->isHovered && frame->can_click_this_frame)\
				{ {INTERACT_CODE;} frame->can_click_this_frame = false;}\
			{EXTEND_CODE;}\
			index--;\
		});\
	}

#define FRAME_ADD_DEFN(TYPE, KEYWORD, FRAMENAME)\
	void frame_add_##KEYWORD(const TYPE* KEYWORD){\
		frame_t* frame = init_frame();\
		place_in_plate(&##KEYWORD##->pos);\
		list_##TYPE##_add(frame->##FRAMENAME, KEYWORD);}


#define FRAME_FUNC_DECL(TYPE, KEYWORD, FRAMENAME)\
	DRAW_FRAME_DECL(TYPE, KEYWORD, FRAMENAME) UPDATE_FRAME_DECL(TYPE, KEYWORD, FRAMENAME) FRAME_ADD_DECL(TYPE, KEYWORD, FRAMENAME)\

#endif
