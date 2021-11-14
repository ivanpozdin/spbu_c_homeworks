#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    TreeMap* map = createTreeMap();
    put(map, 1, 10);
    put(map, 2, 20);
    put(map, 3, 30);
    put(map, 3, 40);
    put(map, 5, 50);
    put(map, 5, 100);
    hasKey(map, 1) ? printf("YES\n") : printf("NO\n");
    prettyPrint(map, '_', 1);
    bool thereIsSuchElement1 = true;
    int lowerBoundValue = getLowerBound(map, 5, &thereIsSuchElement1);
    if (thereIsSuchElement1)
        printf("%d\n", lowerBoundValue);

    bool thereIsSuchElement2 = true;
    int upperBoundValue = getUpperBound(map, 5, &thereIsSuchElement2);
    if (thereIsSuchElement2)
        printf("%d\n", upperBoundValue);
    deleteTreeMap(map);

}