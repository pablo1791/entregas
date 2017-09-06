#include <stdio.h>
#include <stdlib.h>
#include "validar.h"

float suma(float valor1, float valor2)
{
    float result;
    result=valor1+valor2;
    return result;
}

float resta(float valor1, float valor2)
{
    float result;
    result=valor1-valor2;
    return result;
}

float dividir(float dato1, float dato2)

{
    float resultado;
    resultado=dato1 / dato2;
    return resultado;
}

float multiplicar(float valor1, float valor2)
{
    float result;
    result=valor1 * valor2;
    return result;
}

int factorial(float valor)
{
    int i, factoreo=1;
    if(valor<0)
    {
        factoreo=0;
    }
    else if(valor==0)
    {
        factoreo=1;
    }
    else
    {

        for (i=1; i <= valor; i++)
        {
            factoreo=i*factoreo;
        }
    }
    return factoreo;
}



                                 //se unicia resultado en 1 para que cuando lo multipliquemos * i no nos de 0

// se inicia i en 1, el for corre siempre y cuando i sea <= al dato ungresado
// resultado va cambiando a medida que incrementa i




