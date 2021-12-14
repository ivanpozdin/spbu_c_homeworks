#include <stdio.h>
#include <stdlib.h>

typedef struct ComplexNumber {
    double real;
    double imaginary;
} ComplexNumber;

ComplexNumber complexSum(ComplexNumber num1, ComplexNumber num2)
{
    return (ComplexNumber) { num1.real + num2.real, num1.imaginary + num2.imaginary };
}
ComplexNumber complexDifference(ComplexNumber num1, ComplexNumber num2)
{
    return (ComplexNumber) { num1.real - num2.real, num1.imaginary - num2.imaginary };
}
ComplexNumber complexProduct(ComplexNumber num1, ComplexNumber num2)
{
    return (ComplexNumber) { num1.real * num2.real - num2.imaginary * num2.imaginary, num1.real * num2.imaginary + num2.real * num1.imaginary };
}

ComplexNumber complexDivision(ComplexNumber num1, ComplexNumber num2)
{
    double real = (num1.real * num2.real + num1.imaginary * num2.imaginary) / (num2.real * num2.real + num2.imaginary * num2.imaginary);
    double imaginary = (num2.real * num1.imaginary - num1.real * num2.imaginary) / (num2.real * num2.real + num2.imaginary * num2.imaginary);
    return (ComplexNumber) { real, imaginary };
}

int main()
{
    printf("Enter real and imaginary parts of 1st complex number: ");
    ComplexNumber num1;
    scanf("%lf", &num1.real);
    scanf("%lf", &num1.imaginary);

    printf("Enter real and imaginary parts of 2nd complex number: ");
    ComplexNumber num2;
    scanf("%lf", &num2.real);
    scanf("%lf", &num2.imaginary);
    printf("\n");
    ComplexNumber sumOfNumbers = complexSum(num1, num2);
    printf("sum: %f+(%f)i\n", sumOfNumbers.real, sumOfNumbers.imaginary);
    ComplexNumber differenceOfNumbers = complexDifference(num1, num2);
    printf("difference: %f+(%f)i\n", differenceOfNumbers.real, differenceOfNumbers.imaginary);
    ComplexNumber productOfNumbers = complexProduct(num1, num2);
    printf("product: %f+(%f)i\n", productOfNumbers.real, productOfNumbers.imaginary);
    ComplexNumber divisionOfNumbers = complexDivision(num1, num2);
    printf("division: %f+(%f)i\n", divisionOfNumbers.real, divisionOfNumbers.imaginary);
}
