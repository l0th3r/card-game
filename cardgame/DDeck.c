#include "DDeck.h"

DDeck* DDeck_init(Deck_t* deck, bool isHidden, int x, int y)
{
	DDeck* ddeck = malloc(sizeof(DDeck));

	if (ddeck)
	{
		ddeck->pos.x = x;
		ddeck->pos.y = y;

		ddeck->d = deck;
		ddeck->isHidden = isHidden;

		if (deck)
			ddeck->top = &deck->pile[0];
		else
			ddeck->top = NULL;
	}

	return ddeck;
}
