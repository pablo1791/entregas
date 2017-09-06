#include <stdio.h>
#include <stdlib.h>
#include "validar.h"
#include "operacionesMatematicas.h"

int main()
{
    char seguir='s';
    int opcion, flagCargado1=0, flagCargado2=0;
    float num1=0;
    float num2=0;
    float resultSuma;
    float resultResta;
    float resultDiv, resultMult;
    float resultFact;

    while(seguir=='s')
    {
        system("cls");
        printf("1- Ingresar 1er operando \t\t  (A)= %.2f\n", num1);
        printf("2- Ingresar 2do operando \t\t  (B)= %.2f\n", num2);
        printf("3- Calcular la suma      \t\t(A+B)= %.2f\n", resultSuma);
        printf("4- Calcular la resta     \t\t(A-B)= %.2f \n", resultResta);
        printf("5- Calcular la division  \t\t(A/B)= %.2f \n",resultDiv);
        printf("6- Calcular la multiplicacion \t\t(A*B)= %.2f\n", resultMult);
        printf("7- Calcular el factorial \t\t(A!) = %.2f \n", resultFact);
        printf("8- Calcular todas las operaciones\n");
        printf("9- Salir\n");

        tomarDato("\nIngrese opcion: ", "Error, reingrese opcion o 9 para salir: ", &opcion);

        switch(opcion)
        {
        case 1:
            tomarOperando(&num1, &flagCargado1, "numero: ");
            break;
        case 2:
            tomarOperando(&num2, &flagCargado2, "numero: ");
            break;
        case 3:
            resultSuma=suma(num1, num2);
            break;
        case 4:
            resultResta=resta(num1, num2);
            break;
        case 5:
            resultDiv=dividir(num1, num2);
            break;
        case 6:
            resultMult=multiplicar(num1, num2);
            break;
        case 7:
            resultFact=factorial(num1);
            break;
        case 8:
            resultSuma=suma(num1, num2);
            resultResta=resta(num1, num2);
            resultDiv=dividir(num1, num2);
            resultMult=multiplicar(num1, num2);
            resultFact=factorial(num1);
            break;
        case 9:
            seguir = 'n';
            break;
        }
    }
    return 0;
}

