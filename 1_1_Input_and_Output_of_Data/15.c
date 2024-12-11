#include <stdio.h>

void printComplex(double realPart, double imaginaryPart)
{
    int minusSign = imaginaryPart < 0;
    minusSign *= -1;
    int plusSign = ~minusSign;
    printf("%.3lf %c i%.3lf",realPart, '+'+(2*(-minusSign)), imaginaryPart*minusSign + imaginaryPart*(-plusSign));
}

int main(void)
{
    double realPartNumber1 = 0;
    double imaginaryPartNumber1 = 0;

    double realPartNumber2 = 0;
    double imaginaryPartNumber2 = 0;

    printf("Podaj czesc rzeczywista pierwszej liczby zespolonej:  ");
    scanf("%lf", &realPartNumber1);

    printf("Podaj czesc urojona pierwszej liczby zespolonej:  ");
    scanf("%lf", &imaginaryPartNumber1);

    printf("Podaj czesc rzeczywista drugiej liczby zespolonej:  ");
    scanf("%lf", &realPartNumber2);

    printf("Podaj czesc urojona drugiej liczby zespolonej:  ");
    scanf("%lf", &imaginaryPartNumber2);

    printComplex(realPartNumber1, imaginaryPartNumber1);
    printf(" ");
    printComplex(realPartNumber2, imaginaryPartNumber2);
    printf("\n");

    //suma
    printComplex(realPartNumber1 + realPartNumber2, imaginaryPartNumber1 + imaginaryPartNumber2);
    printf("\n");

    //roznica
    printComplex(realPartNumber1 - realPartNumber2, imaginaryPartNumber1 - imaginaryPartNumber2);
    printf("\n");

    //mnozenie
    double tmpRealPart = 0;
    double tmpImaginaryPart = 0;

    tmpRealPart += realPartNumber1 * realPartNumber2;
    tmpRealPart += imaginaryPartNumber1 * imaginaryPartNumber2 * -1;

    tmpImaginaryPart += imaginaryPartNumber1 * realPartNumber2;
    tmpImaginaryPart += imaginaryPartNumber2 * realPartNumber1;

    printComplex(tmpRealPart, tmpImaginaryPart);
    printf("\n");

    //dzielenie
    double topReal = realPartNumber1;
    double topImaginary = imaginaryPartNumber1;
    double bottomReal = realPartNumber2;
    double bottomImaginary = imaginaryPartNumber2;

    topReal *= bottomReal;
    topReal += topImaginary * (-bottomImaginary) * -1;

    topImaginary = topImaginary * bottomReal;
    topImaginary += realPartNumber1 * (-bottomImaginary);

    bottomReal = bottomReal * bottomReal + bottomImaginary * bottomImaginary;

    tmpRealPart = topReal / bottomReal;
    tmpImaginaryPart = topImaginary / bottomReal;

    printComplex(tmpRealPart, tmpImaginaryPart);
    printf("\n");

    return 0;
}