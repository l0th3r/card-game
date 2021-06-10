#pragma once
#ifndef _D_BUTTON_H_
#define _D_BUTTON_H_

#include <raylib.h>
#include <stdbool.h>

#include "mouse_handler.h"

typedef enum
{
    BTN_ADD_DECK = 0,
    BTN_ADD_DISC
} btn_type;

typedef struct
{
    Vector2 pos;
    btn_type type;
    Rectangle buttonRectangle, textRectangle;
    Color color;
    const char* text;
    
    bool isHovered;
    int frame_index;
} DBtn;

DBtn* DBtn_init(btn_type type, const char* content, Color color, int x, int y);

void DBtn_draw(const DBtn* dbtn);

void DBtn_event(const DBtn* dbtn);

void DBtn_destroy(DBtn* dbtn);

#endif
