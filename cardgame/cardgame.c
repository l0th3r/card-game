#include <libcard.h>
#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "DCard.h"
#include "DDeck.h"
#include "DBtn.h"

#include "frame_container.h"
#include "mouse_handler.h"

/* DrawText(TextFormat("x:%d", 10), 20, 20, 5, BLACK); */

int main()
{    
    init_frame();
    srand(time(0));

    InitWindow(1800, 1000, "main window");

    DPlate_init(500, 500, 800, 500);
    DDisc_init(747, 590);
    DBtn_init(BTN_ADD_DECK, "Add Deck", VIOLET, 175, 280);

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

    dest_frame();
    dest_mouse();
    CloseWindow();
    return 0;
}