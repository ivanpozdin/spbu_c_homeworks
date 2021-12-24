#include <stdio.h>

long long f(int n)
{
    long long values[3] = { -1, 0, 1 };

    if (n < 3 && n >= 0)
        return values[n];

    for (int i = 3; i <= n; i++) {
        long long tmp = values[2];
        values[2] = 3 * values[0] + 2 * values[1] + values[2];
        values[0] = values[1];
        values[1] = tmp;
    }
    return values[2];
}

int main()
{
    for (int i = 0; i < 1000; i++)
        printf("%lli\n", f(i));
}
