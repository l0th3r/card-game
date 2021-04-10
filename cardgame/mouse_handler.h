#pragma once
#ifndef _MOUSE_HANDLER_H_
#define _MOUSE_HANDLER_H_

#include <raylib.h>
#include "DCard.h"

/* define mouse struct */
typedef struct
{
	int x, y;		/* mouse X and Y position */
	float wheel;	/* mouse wheel y move */

	bool left;		/* true if mouse left button is pressed */
	bool right;		/* true if mouse right button is pressed */
	bool mid;		/* true if mouse mid button is pressed */

	DCard* holded;
} mouse_t;

/* get mouse struct */
mouse_t* get_mouse();

/* update mouse data (meant to be use every frames) */
void update_mouse();

/* x1 and y1 needs to be < than x2 and y2 */
bool is_mouse_hovering(int x1, int y1, int x2, int y2);

/* check and handle click */
void check_holded();

/* destroy mouse struct */
void dest_mouse();

#endif
