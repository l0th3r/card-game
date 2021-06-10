#pragma once
#ifndef _D_PLATE_H_
#define _D_PLATE_H_

#include <raylib.h>
#include <libcard.h>

#include "mouse_handler.h"

typedef struct
{
	Vector2 pos;
	int width;
	int height;
} DPlate;

DPlate* DPlate_init(int x, int y, int width, int height);

void DPlate_update(DPlate* dplate);

void DPlate_draw(const DPlate* dplate);

bool DPlate_compare_x(DPlate* dplate, const int x);
bool DPlate_compare_y(DPlate* dplate, const int y);

void DPlate_destroy(DPlate* dplate);

#endif