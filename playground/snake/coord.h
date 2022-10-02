#ifndef SNAKE_COORD_
#define SNAKE_COORD_

#include <stdbool.h>

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct CoordList {
    Coord* items;
    size_t lenght;
    size_t container_length;
} CoordList;

typedef struct CoordLinkedList {
    struct CoordLinkedListNode* first;
    struct CoordLinkedListNode* last;
    size_t length;
} CoordLinkedList;

typedef struct CoordLinkedListNode {
    Coord data;
    struct CoordLinkedListNode* next;
    struct CoordLinkedListNode* prev;
} CoordLinkedListNode;


Coord coord_add(Coord a, Coord b);
bool coord_equal(Coord a, Coord b);
Coord coord_mod(Coord a, Coord b);

CoordList coordlist_create();
void coordlist_add(CoordList* coord_list, Coord item);

CoordLinkedList coordlinkedlist_create();
void coordlinkedlist_add(CoordLinkedList* list, Coord item);
void coordlinkedlist_remove(CoordLinkedList* list, CoordLinkedListNode* node);
CoordLinkedListNode* coordlinkedlist_get(CoordLinkedList* list, size_t index);

#endif // SNAKE_COORD_
