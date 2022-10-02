#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "coord.h"

Coord coord_add(Coord a, Coord b) {
    return (Coord) { a.x + b.x, a.y + b.y };
}

bool coord_equal(Coord a, Coord b) {
    return a.x == b.x && a.y == b.y;
}

Coord coord_mod(Coord a, Coord b) {
    return (Coord) { (a.x + b.x) % b.x, (a.y + b.y) % b.y };
}

CoordList coordlist_create() {
    return (CoordList) {(Coord*)malloc(10 * sizeof(Coord)), 0, 10};
}

void coordlist_add(CoordList* coord_list, Coord item) {
    if (coord_list->lenght == coord_list->container_length) {
        size_t new_container_length = coord_list->container_length * 2;
        Coord* new_list = (Coord*)malloc(new_container_length * sizeof(Coord));
        for (size_t i = 0; i < coord_list->lenght; i++) {
            new_list[i] = coord_list->items[i];
        }
        free(coord_list->items);
        coord_list->items = new_list;
        coord_list->container_length = new_container_length;
    }
    coord_list->items[coord_list->lenght] = item;
    coord_list->lenght++;
}

void coordlist_delete(CoordList* list) {
    free(list->items);
}

CoordLinkedList coordlinkedlist_create() {
    return (CoordLinkedList) {NULL, NULL, 0};
}

void coordlinkedlist_add(CoordLinkedList* list, Coord item) {
    CoordLinkedListNode* new_node = (CoordLinkedListNode*)malloc(sizeof(CoordLinkedListNode));
    new_node->data = item;
    new_node->next = NULL;
    new_node->prev = NULL;
    list->length++;

    if (list->first == NULL) {
        list->first = new_node;
        list->last = new_node;
        return;
    }

    CoordLinkedListNode* node = list->first;
    while(node->next != NULL)
        node = node->next;

    node->next = new_node;
    new_node->prev = node;
}

void coordlinkedlist_remove(CoordLinkedList* list, CoordLinkedListNode* item) {
    if (item->prev != NULL)
        item->prev->next = item->next;
    if (item->next != NULL)
        item->next->prev = item->prev;
    list->length--;
    free(item);
}

CoordLinkedListNode* coordlinkedlist_get(CoordLinkedList* list, size_t index) {
    CoordLinkedListNode* node = list->first;
    while(node != NULL && index-- > 0)
        node = node->next;
    if (!index == 0)
        return NULL;
    return node;
}
