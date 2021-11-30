#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    TreeMap* map = createTreeMap();
    put(map, wrapInt(1), wrapInt(10));
    put(map, wrapInt(2), wrapInt(20));
    put(map, wrapInt(2), wrapInt(40));
    put(map, wrapInt(3), wrapInt(30));
    put(map, wrapInt(5), wrapInt(50));
    put(map, wrapInt(6), wrapInt(60));


    //printf("%d", getInt(removeKey(map, wrapInt(2)).value));
    TreeMapIterator* iterator = getIterator(map);
    hasElement(iterator) ? printf("%d\n", getInt(getKey(iterator))) : printf("NO\n");
    next(iterator, true);
    hasElement(iterator) ? printf("%d\n", getInt(getKey(iterator))) : printf("NO\n");
    next(iterator, true);
    hasElement(iterator) ? printf("%d\n", getInt(getKey(iterator))) : printf("NO\n");
    next(iterator, true);
    hasElement(iterator) ? printf("%d\n", getInt(getKey(iterator))) : printf("NO\n");
    next(iterator, true);
    hasElement(iterator) ? printf("%d\n", getInt(getKey(iterator))) : printf("NO\n");
    next(iterator, true);
    //hasElement(iterator) ? printf("%d\n", getInt(getKey(iterator))) : printf("NO\n");
    deleteTreeMap(map);
}