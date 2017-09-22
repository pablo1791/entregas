#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaciones.h"
#include "funciones.h"

/** \brief inicializa en array en lugar libre (0)
 *
 * \param array del tipo persona
 * \param tamaño de array
 * \return 0
 *
 */
int persona_initArray (EPersona* arrayPersona, int longitud)
{
    int i;
    if(arrayPersona != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            arrayPersona[i].estado = LUGAR_LIBRE; // lugar libre es 0
        }

    }
    return 0;
}


/** \brief busca el proximo id/indice libre del array
 *
 * \param array del tipo persona
 * \param tamaño de array
 * \return retorna i (indice libre) retorna o -1 si no hay lugar libre
 *
 */
int persona_buscaProxId (EPersona* arrayPersona, int longitud)
{
    int i, retorno = -1;
    if(arrayPersona != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            if(arrayPersona[i].estado == LUGAR_LIBRE)
            {
                retorno = i;
            }
        }
    }
    return retorno;
}
/** \brief carga datos de estructura persona
 *
 * \param array del tipo persona
 * \param tamaño de array
 * \return o si se cargo el dato, -1 si no se pudo cargar.
 *
 */
int persona_cargarPersona (EPersona* arrayPersona, int longitud)
{
    int retorno = -1;
    char bNombre[50];
    char bDni[15];
    char bEdad[4];
    int auxId;

    if(arrayPersona != NULL && longitud > 0)
    {
        if(val_getString(bNombre,"\nNOMBRE?","\nError:\n",3,50)==0)
        {
            if(val_getStringDni(bDni,"\nDNI?","\nError:\n",3,15)==0)
            {
                if(val_getUnsignedInt(bEdad,"\nEDAD?","\nError:\n",3,4)==0)
                {
                    auxId=persona_buscaProxId(arrayPersona,longitud);
                    if(auxId!=-1)
                    {
                        strncpy(arrayPersona[auxId].nombre, bNombre, 50);
                        strncpy(arrayPersona[auxId].dni, bDni, 15);
                        arrayPersona[auxId].edad = atoi(bEdad);
                        arrayPersona[auxId].estado= LUGAR_OCUPADO;
                        retorno=0;
                    }
                }
            }
        }
    }
    return retorno;
}
/** \brief da de baja datos de estructura persona
 *
 * \param array del tipo persona
 * \param tamaño de array
 * \return o si se dio de baja el dato, -1 si no se pudo
 *
 */
int persona_bajaPersona (EPersona* arrayPersona,int longitud)
{
    int retorno = -1;
    char bDni[15];
    int index;

    if(arrayPersona != NULL && longitud >= 0)
    {
        val_getStringDni(bDni, "dni\n", "error\n", 3, 15);
        index=persona_buscarPorDni(arrayPersona, bDni, longitud, "error en buscar por dni\n");
        if(index!=-1)
        {
            arrayPersona[index].estado=LUGAR_LIBRE;
            retorno=0;
        }
    }
    return retorno;
}
/** \brief busca el dni (ingresado por el usuario) en el array
 *
 * \param array del tipo persona
 * \param dni ingresado por el usuario en la funcion buscar por dni
 * \param tamaño de array
 * \param mensaje de error
 * \return retorna i (indice del dni) retorna o -1 si no se encontro dni
 *
 */
int persona_buscarPorDni(EPersona* arrayPersona, char* dni, int longitud,char mensajeError[])
{
    int i;
    int retorno=-1;
    if(arrayPersona != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            if(arrayPersona[i].estado == LUGAR_OCUPADO)
            {
                if(stricmp(dni, arrayPersona[i].dni)==0)
                {
                    retorno=i;

                    break;
                }
                else
                {
                    printf(mensajeError);
                    retorno = -1;

                    break;
                }
            }
        }
    }

    return retorno;
}
/** \brief ordena el array persona alfabeticamente por campo nombre
 *
 * \param array del tipo persona
 * \param tamaño de array
 * \return 0
 */
int persona_ordenar(EPersona* arrayPersona, int longitud)
{
    int i, j;
    EPersona aux;
    for(i=0 ; i<longitud-1; i++)
    {
        for(j=i+1; j>0 ; j--)
        {
            if((stricmp(arrayPersona[j].nombre, arrayPersona[j-1].nombre))<0)
            {
                aux=arrayPersona[j];
                arrayPersona[j]=arrayPersona[j-1];
                arrayPersona[j-1]=aux;
            }
        }
    }
    return 0;

}

/** \brief imprime el array ordenado alfabeticamente
 *
 * \param array del tipo persona
 * \param tamaño de array
 * \return 0
 *
 */
int persona_printPersona (EPersona* arrayPersona, int longitud)
{
    int i;
    if(arrayPersona != NULL && longitud > 0)
    {
        persona_ordenar(arrayPersona, longitud);
        for(i=0; i<longitud ; i++)
        {
            if(arrayPersona[i].estado == LUGAR_OCUPADO)
            {
                printf("\nNombre: %s\nDNI: %s\nEdad: %d\n",arrayPersona[i].nombre, arrayPersona[i].dni, arrayPersona[i].edad);
            }
        }
    }
    return 0;
}

/** \brief imprime grafico de edades
 *
 * \param array del tipo persona
 * \param tamaño de array
 * \return void
 *
 */
void persona_imprimirGraficoEdades(EPersona arrayPersona[],int longitud)
{
    int contMenos18 = 0;
    int contEntre18_35 = 0;
    int contMas35 = 0;
    int i,listaA,listaB,listaC;
    char menos18[] = "Menos de 18";
    char entre18y35[] = "Entre 18 y 35";
    char mayores35[] = "Mayores de 35";

    for(i=0; i<longitud; i++)
    {
        if(arrayPersona[i].estado == 1)
        {
            if(arrayPersona[i].edad < 18)
            {
                contMenos18++;
            }
            else if(arrayPersona[i].edad <35)
            {
                contEntre18_35++;
            }
            else
            {
                contMas35++;
            }
        }

    }
        listaA= contMenos18;
        listaB = contEntre18_35;
        listaC = contMas35;


    for(i=longitud; i>0; i--)
    {

            if(i==listaA)
            {
                printf("\n  *\t\t");
                listaA--;
            }
            else
            {
                printf(" \t\t");
            }

            if(i==listaB)
            {
                printf("  *\t\t");
                listaB--;
            }
            else
            {
                printf(" \t\t");
            }
            if(i==listaC)
            {
                printf("  *\t\t");
                listaC--;
            }
            else
            {
                printf(" \t\n");
            }
    }
        printf("\n%s\t%s\t%s\n",menos18,entre18y35,mayores35);
}





