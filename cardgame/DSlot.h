#pragma once
#ifndef _D_SLOT_H_
#define _D_SLOT_H_

#include <raylib.h>
#include "DCard.h";
#include "DSizes.h";

typedef struct
{
	Vector2 pos;
	DCard* holded;

	bool isHovered;
} DSlot;


#endif