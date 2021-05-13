#pragma once
#ifndef _FOREACH_H_
#define _FOREACH_H_

#define FOREACH_LIST(ITEM_TYPE, ITEM, LIST, CODE)\
	for(list_node* LIST_NODE = LIST->begin; LIST_NODE != NULL; LIST_NODE = LIST_NODE->next)\
		{ ITEM_TYPE* ITEM = (ITEM_TYPE*)LIST_NODE->data; CODE}

#endif