#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validar.h"

#define MAX_INPUT_BUFFER 4096

/** \brief recibe un buffer y el la ultima posicion coloca un /0
 *
 * \param buffer. donde cargo el string
 * \param limite tamaño del string
 * \param
 * \return void
 *
 */
void myFgets(char* buffer, int limite,FILE* archivo)
{
    int i=0;
    fflush(archivo);
    fgets(buffer, limite,archivo);
    buffer[limite-1] = '\0';
    while(buffer[i] != '\0')
    {
        if(buffer[i] == 10) //10 -> LF
        {
            buffer[i] = '\0';
            break;
        }
        i++;
    }
}
/** \brief valida que solo se ingresen letras
 *
 * \param destino. donde se guarda el estrig
 * \param mensaje del usuario
 * \param mensaje de error
 * \param intentos. cantidad de intentos que puede realizar ante un error
 * \param limite. tamaña del string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_getString(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarString(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/** \brief valida que solo se ingresen letras y espacios
 *
 * \param buffer donde se guarda el string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_validarString(char* buffer)
{
    int i=0;
    int retorno = 0;

    if(buffer[i] == '0')
        retorno = -1;

    while(buffer[i] != '\0')
    {
        if((buffer[i] < 'a' || buffer[i] > 'z') && (buffer[i] < 'A' || buffer[i] > 'Z') && buffer[i] != ' ')
        {
            retorno = -1;
            break;
        }
        i++;
    }
    return retorno;
}

/** \brief valida que solo se un formato DNI
 *
 * \param destino. donde se guarda el estrig
 * \param mensaje del usuario
 * \param mensaje de error. mensaje de error en caso de -1
 * \param intentos. cantidad de intentos que puede realizar ante un error
 * \param limite. tamaña del string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_getDNI(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarDni(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
/** \brief valida que solo se ingresen numeros y puntos
 *
 * \param buffer donde se guarda el string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_validarDni(char* buffer)
{
    int i=0;
    int retorno = 0;
    int flagPunto = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '.')
        {
            retorno = -1;
            break;
        }
        else
        {
            if((buffer[i] == '.' && i == 2) || (buffer[i] == '.' && i == 6))
            {
                flagPunto++;
            }
        }
        i++;
    }
    if(flagPunto != 2)
    {
        retorno = -1;
    }
    return retorno;
}

/** \brief valida numeros enteros
 *
 * \param destino. donde se guarda el estrig
 * \param mensaje del usuario
 * \param mensaje de error. mensaje de error en caso de -1
 * \param intentos. cantidad de intentos que puede realizar ante un error
 * \param limite. tamaña del string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_getUnsignedInt(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarUnsignedInt(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/** \brief valida que solo se ingresen numeros
 *
 * \param buffer donde se guarda el string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_validarUnsignedInt(char* buffer)
{
    int i=0;
    int retorno = 0;
    int flagPunto = 0;
    while(buffer[i] != '\0')
    {
        if(buffer[i] < '0' || buffer[i] > '9' )
        {
            retorno = -1;
            break;
        }
        else
        {
            if(buffer[i] == '-' && i != 0)
            {
                retorno = -1;
                break;
            }
            else if(buffer[i] == '.')
            {
                flagPunto++;
                if(flagPunto > 1)
                {
                    retorno = -1;
                    break;
                }
            }
        }
        i++;
    }
    return retorno;
}

/** \brief valida que se ingrese edad valida dentro de un rango
 *
 * \param destino. donde se guarda el estrig
 * \param mensaje del usuario
 * \param mensaje de error. mensaje de error en caso de -1
 * \param intentos. cantidad de intentos que puede realizar ante un error
 * \param limite. tamaña del string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_getUnsignedEdad(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = 0;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {
            myFgets(buffer, limite,stdin);

            if(val_validarUnsignedEdad(buffer) == -1 || (atoi(buffer) < 0 || atoi(buffer) > 100))
            {
                printf(mensajeError);
                retorno = -1;
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
            }
            break;
        }
    }
    return retorno;
}

/** \brief valida que solo se ingresen numeros
 *
 * \param buffer donde se guarda el string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_validarUnsignedEdad(char* buffer)
{
    int i=0;
    int retorno = 0;
    while(buffer[i] != '\0')
    {
        if(buffer[i] < '0' || buffer[i] > '9' )
        {
            retorno = -1;
            break;
        }
        i++;
    }
    return retorno;
}

/** \brief toma un string ingresado por el usuario
 *
 * \param destino. donde se guarda el estrig
 * \param mensaje del usuario
 * \param mensaje de error. mensaje de error en caso de -1
 * \param intentos. cantidad de intentos que puede realizar ante un error
 * \param limite. tamaña del string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_getAlfanumericoConSigno(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarAlfanumerico(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/** \brief valida que solo se ingresen numeros, letras y signos
 *
 * \param buffer donde se guarda el string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_validarAlfanumerico(char* buffer)
{
    int i=0;
    int retorno = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < 'a' || buffer[i] > 'z') &&
                (buffer[i] < 'A' || buffer[i] > 'Z') && (buffer[i] < '0' || buffer[i] > '9') &&
                (buffer[i] != '.') && (buffer[i] != '-') && (buffer[i] != '_') && (buffer[i] != '@') && (buffer[i] != ' ' ) &&
                (buffer[i] != '/' ) && (buffer[i] != ':' ) && (buffer[i] != '.' ))
        {
            retorno = -1;
            break;
        }
        i++;
    }
    return retorno;
}

/** \brief toma un string para validar formato email
 *
 * \param destino. donde se guarda el estrig
 * \param mensaje del usuario
 * \param mensaje de error. mensaje de error en caso de -1
 * \param intentos. cantidad de intentos que puede realizar ante un error
 * \param limite. tamaña del string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_getEmail(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarEmail(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/** \brief valida que se ingresen caracteres correspondientes a un email y que el @ no correspoda a el primer caracter y que no
            contengas mas de 1 @
 *
 * \param buffer donde se guarda el string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_validarEmail(char* buffer)
{
    int i=0;
    int retorno = 0;
    int contador=0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < 'a' || buffer[i] > 'z') &&
                (buffer[i] < 'A' || buffer[i] > 'Z') && (buffer[i] < '0' || buffer[i] > '9') &&
                (buffer[i] != '.') && (buffer[i] != '-') && (buffer[i] != '_') && (buffer[i] != '@'))
        {
            retorno = -1;
            break;
        }
        if(buffer[i] == '@' && i == 0)
        {
            retorno=-1;
        }
        else if(buffer[i]=='@')
        {
            contador ++;
        }
        if(contador == 1)
        {
            retorno=0;
        }
        i++;
    }
    return retorno;
}

/** \brief toma un string para validar que el string sea flotante
 *
 * \param destino. donde se guarda el estrig
 * \param mensaje del usuario
 * \param mensaje de error. mensaje de error en caso de -1
 * \param intentos. cantidad de intentos que puede realizar ante un error
 * \param limite. tamaña del string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_getFloat(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarFloat(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/** \brief valida que solo se ingresen numeros y que contenga 1 punto o - (en la primer posicion)
 *
 * \param buffer donde se guarda el string
 * \return -1 si no se pudo cargar. 0 si la carga se realizo
 *
 */
int val_validarFloat(char* buffer)
{
    int i=0;
    int retorno = 0;
    int flagPunto = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '.' && buffer[i] != '-' )
        {
            retorno = -1;
            break;
        }
        else
        {
            if(buffer[i] == '-' && i != 0)
            {
                retorno = -1;
                break;
            }
            else if(buffer[i] == '.')
            {
                flagPunto++;
                if(flagPunto > 1)
                {
                    retorno = -1;
                    break;
                }
            }
        }
        i++;
    }
    return retorno;
}


/** \brief Valida que solo se ingrese Cuit
 *
 * \param destino donde se guarda el string
 * \param mensaje para el usuario
 * \param mensajeError para el usuario
 * \param intentos cantidad de intentos si no cumple con la validacion
 * \param limite tamaño del string
 * \return 0 ok -1 error
 *
 */
int val_getCuit(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarCuit(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}



/** \brief valida que solo se ingresen numeros y guiones
 *
 * \param buffer donde se guarda
 * \return 0 ok y -1 error
 */
int val_validarCuit(char* buffer)
{
    int i=0;
    int retorno = 0;
    int flagGuion = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '-')
        {
            retorno = -1;
            break;
        }
        else
        {
            if((buffer[i] == '-' && i == 2) || (buffer[i] == '-' && i == 11))
            {
                flagGuion++;
            }
        }
        i++;
    }
    if(flagGuion != 2)
    {
        retorno = -1;
    }
    return retorno;
}

