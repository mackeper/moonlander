#include <stdbool.h>
#include <stdlib.h>

#include "direction.h"

bool direction_is_opposite(Direction dir1, Direction dir2) {
    return abs((int)dir1 - (int)dir2) == 2;
}
