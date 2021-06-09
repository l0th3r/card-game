#pragma once
#ifndef _D_CARD_H_
#define _D_CARD_H_

#include <raylib.h>
#include <stdbool.h>

#include "libcard.h"
#include "mouse_handler.h"

typedef struct
{
    Vector2 pos;
    Card_t* c;
    bool isTaken;
    bool isHovered;
    int frame_index;
} DCard;

/* init a new dcard (liked to a Card_t != NULL) */
DCard* DCard_init(Card_t* card, int x, int y);

/* return true if the card is getting hovered */
bool is_card_hovered(DCard* dcard);

/* draw and update status of a dcard */
void DCard_update(DCard* dcard);

/* return the proper string for a dcard's card */
char* format_card_graphics(const Card_t* card, Color* color);

/* display the card */
void DCard_draw(const DCard* dcard);

/* destroy dcard */
void DCard_destroy(DCard* dcard);

#endif