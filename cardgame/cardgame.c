#include <libcard.h>
#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "mouse_handler.h"
#include "DCard.h"

/* DrawText(TextFormat("x:%d", 10), 20, 20, 5, BLACK); */

int main()
{
    DCard* card;
    Deck_t* deck = create_classic_52(2);
    
    srand(time(0));

    shuffle_deck(deck);
    card = DCard_init(get_random_card(deck), 100, 100);

    InitWindow(1800, 1000, "main window");
    /* RUNTIME */
    while (!WindowShouldClose())
    {
        update_mouse();
        
       
        /* DRAW SECTION */
        BeginDrawing();
        ClearBackground(RAYWHITE);

        update_card(card);

        EndDrawing();
    }

    dest_mouse();

    CloseWindow();
    return 0;
}