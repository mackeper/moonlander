#ifndef COLLECTIONS_LIST_
#define COLLECTIONS_LIST_

#include <stdlib.h>

#define LIST(type) \
    struct list_type {\
        type* items;\
        size_t item_size;\
        size_t length;\
    }\


LIST(int);

#endif // COLLECTIONS_LIST_
