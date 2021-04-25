#pragma once
#ifndef _D_CARD_H_
#define _D_CARD_H_

#include <raylib.h>
#include "libcard.h"

#define CW 50	/* CARD WIDTH */
#define CH 80	/* CARD HEIGHT */
#define CBOR 4	/* CARD BORDER (need to be even) */
#define CFS 20  /* CARD FONT SIZE */

typedef struct
{
    int x, y;
    Card_t* c;
    bool taken;
} DCard;

/* init a new dcard (liked to a Card_t != NULL) */
DCard* DCard_init(Card_t* card, int x, int y);

/* return true if the card is getting hovered */
bool is_card_hovered(DCard* dcard);

void update_card(DCard* dcard);

/* display the card */
void DCard_draw(const DCard* dcard);

#endif