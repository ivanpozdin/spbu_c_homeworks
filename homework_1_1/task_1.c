#include <stdio.h>
#include <stdlib.h>

int countQuotient(int dividend, int divisor)
{
	int quotient = 0, absDividend = abs(dividend), absDivisor = abs(divisor);
	while (absDividend >= absDivisor) {
		absDividend -= absDivisor;
		++quotient;
	}

	if (dividend < 0) {
		quotient = -quotient - 1;
	}
	if (divisor < 0) {
		quotient = -quotient;
	}
	return quotient;
}

int main()
{
	int dividend, divisor;
	printf("Введите делимое и делитель: ");
	scanf("%i %i", &dividend, &divisor);
	printf("Неполное частное равно %i", countQuotient(dividend, divisor));
	return 0;
}
