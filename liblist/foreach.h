#pragma once
#ifndef _FOREACH_H_
#define _FOREACH_H_

#include "list.h"

#define FOREACH_LIST(ITEM_TYPE, ITEM, LIST, CODE)\
	for(list_node* LIST_NODE = LIST->begin; LIST_NODE != NULL; LIST_NODE = LIST_NODE->next)\
		{ ITEM_TYPE* ITEM = (ITEM_TYPE*)LIST_NODE->data; CODE}

#define FOREACH_LIST_REVERSE(ITEM_TYPE, ITEM, LIST, CODE)\
	for(int i = LIST->count - 1; i >= 0; i--)\
		{ ITEM_TYPE* ITEM = (ITEM_TYPE*)list_get(LIST, i); CODE}

#endif