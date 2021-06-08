#ifndef LIST_LIB
#define LIST_LIB

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* actual node of the chain */
typedef struct list_node list_node;
struct list_node
{
    void* data;
    list_node* next;
};

/* point to the first node, hold the number of nodes */
typedef struct
{
    list_node* begin;
    size_t count;
} list;

/* Initialize the list */
list* create_list();

/* Return the number of nodes in the list */
size_t list_count(const list* _list);

/* Return the node at the given index */
list_node* list_get_node(list* _list, size_t _index);

/* Add a new node at the end of the list with the given data */
size_t list_add(list* _list, void* _data);

/* Return the data of a node */
void* list_get(list* _list, size_t _index);

/* Set the data of a node, return true if successful */
bool list_set(list* _list, size_t _index, void* data);

/* Insert a new node at a certain index with the given data return true if successful */
bool list_insert(list* _list, size_t _index, void* _data);

/* Remove node and data at this index */
bool list_remove(list* _list, size_t _index);

/* Clear and remove all the list (not the data) */
void destroy_list(list* _list);

#endif