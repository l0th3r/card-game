#include "DPlate.h"
#include "DSizes.h"

DPlate* DPlate_init(int x, int y, int width, int height)
{
	DPlate* dplate = malloc(sizeof(DPlate));

	if (dplate)
	{
		dplate->pos.x = x;
		dplate->pos.y = y;
		dplate->width = width;
		dplate->height = height;

		frame_add_plate(dplate);
	}

	return dplate;
}

void DPlate_update(DPlate* dplate)
{
	DPlate_draw(dplate);
}

void DPlate_draw(const DPlate* dplate)
{
	int posX = dplate->pos.x - dplate->width / 2;
	int posY = dplate->pos.y - dplate->height / 2;

	DrawRectangle(posX - PP / 2, posY - PP / 2, dplate->width + PP, dplate->height + PP, LIGHTGRAY);

	DrawRectangle(posX, posY, dplate->width, dplate->height, RAYWHITE);
}

bool DPlate_compare_x(DPlate* dplate, const int x)
{
	return (x >= dplate->pos.x - dplate->width / 2 && x <= dplate->pos.x + dplate->width / 2);
}

bool DPlate_compare_y(DPlate* dplate, const int y)
{
	return (y >= dplate->pos.y - dplate->height / 2 && y <= dplate->pos.y + dplate->height / 2);
}

void DPlate_destroy(DPlate* dplate)
{
	free(dplate);
}