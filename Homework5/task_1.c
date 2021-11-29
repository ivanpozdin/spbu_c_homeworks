#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    TreeMap* map = createTreeMap();
    put(map, wrapInt(1), wrapInt(10));
    put(map, wrapInt(2), wrapInt(20));
    put(map, wrapInt(3), wrapInt(30));
    printf("%d\n", getInt(removeKey(map, wrapInt(2)).key));
    printf("%d", getInt(removeKey(map, wrapInt(2)).value));

    deleteTreeMap(map);
}