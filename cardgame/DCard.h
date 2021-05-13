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
} DCard;

/* init a new dcard (liked to a Card_t != NULL) */
DCard* DCard_init(Card_t* card, int x, int y);

/* return true if the card is getting hovered */
bool is_card_hovered(DCard* dcard);

void update_card(DCard* dcard);

/* display the card */
void DCard_draw(const DCard* dcard);

#endif