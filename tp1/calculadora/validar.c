#include <stdio.h>
#include <stdlib.h>
/** \brief esta funcion toma que funcion voy a realizar del menu
 *
 * \param mensaje "ingresar opcion"
 * \param mensaje de error de opcion.
 * \return retorno 0
 *
 */

int tomarDato(char mensaje[], char mensajeError[], int* valor)
{
    printf(mensaje);
    scanf("%d", valor);
    while(*valor>9 || *valor <= 0)
    {
        printf(mensajeError);
        scanf("%d", valor);
    }
    return 0;
}

/** \brief esta funcion toma el numero para la operacion matematica
 *
 * \param valor ingresado.
 * \param badera de estado de numero cargado o no.
 * \return retorno 0 si esta vacio o no esta cargado y 1 si esta cargado
 *
 */
int tomarOperando(float* valor, int* flagEstado, char mensaje[])
{
    int devolverCargadoNoCargado= 0;
    if(devolverCargadoNoCargado==0)
    {
        devolverCargadoNoCargado=1;
        printf("%s", mensaje);
        scanf("%f", valor);
    }
    *flagEstado=devolverCargadoNoCargado;
    return devolverCargadoNoCargado;
}







