#include <libcard.h>
#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "DCard.h"
#include "DDeck.h"
#include "DSlot.h"

#include "frame_container.h"
#include "mouse_handler.h"

/* DrawText(TextFormat("x:%d", 10), 20, 20, 5, BLACK); */

int main()
{    
    init_frame();
    srand(time(0));

    InitWindow(1800, 1000, "main window");

    update_mouse();
    /* RUNTIME */
    while (!WindowShouldClose())
    {
        update_mouse();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        update_frame();

        EndDrawing();
    }

    dest_mouse();
    dest_frame();
    CloseWindow();
    return 0;
}