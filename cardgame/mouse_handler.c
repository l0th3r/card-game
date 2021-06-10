#include "mouse_handler.h"

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>

#include "DCard.h"
#include "DSizes.h"
#include "DPlate.h"
#include "frame_container.h"

/*DrawText(TextFormat("x=%0.f y=%0.f", m->holded->x, m->holded->y), 5, 5, 10, BLACK);*/

mouse_t* get_mouse()
{
	static mouse_t* mouse = NULL;

	if (!mouse)
	{
		mouse = malloc(sizeof(mouse_t));
		if(mouse)
		{
			mouse->x = 0;
			mouse->y = 0;
			mouse->wheel = 0;

			mouse->left_p = false;
			mouse->left_r = false;
			mouse->left = false;

			mouse->right_p = false;
			mouse->right_r = false;
			mouse->right = false;

			mouse->mid = false;

			mouse->holded = NULL;
		}
	}
	return mouse;
}

void update_mouse()
{
	mouse_t* m = get_mouse();

	m->x = GetMouseX();
	m->y = GetMouseY();
	m->wheel = GetMouseWheelMove();

	m->left_p = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
	m->left_r = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	m->left = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
	
	m->right_p = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
	m->right_r = IsMouseButtonReleased(MOUSE_RIGHT_BUTTON);
	m->right = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);

	m->mid = IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON);

	check_holded();
}

bool is_mouse_hovering(int x1, int y1, int x2, int y2)
{
	mouse_t* m = get_mouse();

	if ((m->x >= x1 && m->x <= x2) && (m->y >= y1 && m->y <= y2))
		return true;
	else
		return false;
}

bool is_object_hovered(Vector2* coord)
{
	mouse_t* m = get_mouse();

	if (is_mouse_hovering(coord->x - CW / 2, coord->y - CH / 2, coord->x + CW / 2, coord->y + CH / 2))
		return true;
	else
		return false;
}

void mouse_release()
{
	mouse_t* m = get_mouse();
	m->holded = NULL;
}

void grab_object(Vector2* coord)
{
	mouse_t* m = get_mouse();

	if (!m->holded)
		m->holded = coord;
}

void check_holded()
{
	mouse_t* m = get_mouse();
	frame_t* f = init_frame();

	if (m->holded != NULL)
	{
		if (m->right_r)
			m->holded = NULL;
		else
		{
			if(f->plate)
			{
				if(DPlate_compare_x(f->plate, m->x))
					m->holded->x = m->x;

				if (DPlate_compare_y(f->plate, m->y))
					m->holded->y = m->y;
			}
			else
			{
				m->holded->x = m->x;
				m->holded->y = m->y;
			}
		}
	}
}

void dest_mouse()
{
	free(get_mouse());
}