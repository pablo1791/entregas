#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "validar.h"

/** \brief inicializa el los campos del array
 * \param array. estructura recibida por referencia
 * \param longitud. tamaño del array
 * \return 0 ok -1 error
 *
 */
int movie_initArray (EMovie* arrayMovie, int longitud)
{
    int retorno = -1;
    int i;
    if(arrayMovie != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            arrayMovie[i].estado = MOVIE_NO_CARGADA;
            retorno=0;
        }
    }
    return retorno;
}


/***************************************************************************************************/

/** \brief genera un id auto-incrementable
 *
 * \return id
 *
 */
static int idAutoincrementable = -1;

int movie_generarProximoId (void)
{
    idAutoincrementable++;
    return idAutoincrementable;
}


/***************************************************************************************************/

/** \brief da de alta una pantalla
 * \param arrayPersona del tipo de dato pantalla
 * \param longitud  tamaño del array
 * \return 0 si se realizo la carga correctamente o -1 si no se pudo realizar la carga
 *
 */
int movie_cargarMovie (EMovie* arrayMovie,int longitud)
{
    char titulo[20];
    char duracion[20];
    char descripcion[50];
    char puntaje[20];
    char linkImagen[50];
    char opcion[10];
    int retorno = -1;
    int i, indice, contadorIntentos=0;
    int flagMotivo = 0;

    if(arrayMovie != NULL && longitud > 0)
    {
        for(i=0; i<longitud; i++)
        {
            if(arrayMovie[i].estado == MOVIE_NO_CARGADA)
            {
                indice = i;
                break;
            }
        }

        if(val_getAlfanumericoConSigno(titulo,"\nNombre de film: ","\nError\n",3,20)==0)
        {
            if(val_getAlfanumericoConSigno(descripcion,"\nDescripion: ","\nError\n",3,50)==0)
            {
                if(val_getUnsignedInt(duracion, "\nDuracion: ", "\nError\n",3,20)== 0)
                {
                    if(val_getUnsignedInt(puntaje, "\nPuntaje: ", "\nError\n",3,20)== 0)
                    {
                        if(val_getAlfanumericoConSigno(linkImagen, "\nLink a imagen: ", "\nError\n",3,50)== 0)
                        {
                            do
                            {
                                val_getUnsignedInt(opcion, "\nGenero\n1-Comedia\n2-Terror\n3-Drama\n4-Ficcion\n5-Suspenso\n", "Opcion incorrecta\n", 3, 10);
                                switch(atoi(opcion))
                                {
                                case 1:
                                    arrayMovie[i].genero = GENERO_COMEDIA;
                                    flagMotivo = 1;
                                    break;
                                case 2:
                                    arrayMovie[i].genero = GENERO_TERROR;
                                    flagMotivo = 1;
                                    break;
                                case 3:
                                    arrayMovie[i].genero = GENERO_DRAMA;
                                    flagMotivo = 1;
                                    break;
                                case 4:
                                    arrayMovie[i].genero = GENERO_FICCION;
                                    flagMotivo = 1;
                                    break;
                                case 5:
                                    arrayMovie[i].genero = GENERO_SUSPENSO;
                                    flagMotivo = 1;
                                    break;
                                }
                                contadorIntentos ++;
                            }
                            while (flagMotivo == 0 && contadorIntentos < 3);
                        }
                    }
                }
                if(flagMotivo==1)
                {
                    strncpy(arrayMovie[indice].titulo, titulo, 20);
                    strncpy(arrayMovie[indice].descripcion, descripcion, 50);
                    arrayMovie[indice].duracion = atoi(duracion);
                    arrayMovie[indice].puntaje = atoi(puntaje);
                    strncpy(arrayMovie[indice].linkImagen, linkImagen, 50);
                    arrayMovie[indice].id = movie_generarProximoId();
                    arrayMovie[indice].estado = MOVIE_CARGADA;
                    movie_VolcarArchivoMovies(arrayMovie, longitud);
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}

/***************************************************************************************************/

/** \brief recorre el array buscando un indice utilizando un id
 *
 * \param array. estructura recibida por referencia
 * \param longitud. tamaño del array
 * \param id recibido para buscar indice
 * \param mensaje
 * \return 0 ok -1 error
 *
 */
int movie_buscarIndicePorId (EMovie* arrayMovie, int longitud, int id, char* mensaje)
{
    int retorno = -1, i;

    if(arrayMovie != NULL && longitud > 0 && id >= 0)
    {
        for(i=0; i<longitud ; i++)
        {
            if(arrayMovie[i].id == id)
            {
                retorno = i;
                break;
            }
        }
        if(retorno == -1)
        {
            printf("%s", mensaje);
        }
    }
    return retorno;
}

/***************************************************************************************************/

/** \brief recorre el array para hacer una baja logica
 *
 * \param array recibido porreferencia
 * \param longitud tamaño del array
 * \return 0 ok -1 error
 *
 */
int movie_darDeBaja (EMovie* arrayMovie,int longitud, char* msjError)
{
    int i, idAux, indice, retorno = -1;
    char buffer[10];

    if(arrayMovie != NULL && longitud > 0)
    {
        for(i=0; i<longitud; i++)
        {
            if(arrayMovie[i].estado != MOVIE_NO_CARGADA)
            {
                if(val_getUnsignedInt(buffer,"Ingrese el ID de pelicula a dar de baja: ", "El ID no se encontro",3,10)==0)
                {
                    idAux = atoi(buffer);
                    indice = movie_buscarIndicePorId(arrayMovie,longitud,idAux, "No se encontro el id");

                    if(indice != -1)
                    {
                        arrayMovie[indice].estado = MOVIE_NO_CARGADA;
                        movie_VolcarArchivoMovies(arrayMovie, longitud);
                        retorno = 0;
                        break;
                    }
                }
            }
            else
            {
                printf(msjError);
                break;
            }
        }
    }
    return retorno;
}

int movie_modificar (EMovie* arrayMovie,int longitud, char* msjError)
{
    int idAux, i, indice, contadorIntentos=0, flagMotivo = 0, retorno = -1;
    char titulo[20];
    char duracion[20];
    char descripcion[50];
    char puntaje[20];
    char linkImagen[50];
    char opcion[10];
    char buffer[10];

    if(arrayMovie != NULL && longitud > 0)
    {
        for(i=0; i<longitud; i++)
        {
            if(arrayMovie[i].estado != MOVIE_NO_CARGADA)
            {
                if(val_getUnsignedInt(buffer,"Ingrese el ID de pelicula a modificar: ", "El ID no se encontro",3,10) == 0)
                {
                    idAux = atoi(buffer);
                    indice = movie_buscarIndicePorId(arrayMovie,longitud,idAux, "No se encontro el id");
                    if(indice!=-1)
                    {

                        if(val_getAlfanumericoConSigno(titulo,"\nNombre de film: ","\nError\n",3,20)==0)
                        {
                            if(val_getAlfanumericoConSigno(descripcion,"\nDescripion: ","\nError\n",3,50)==0)
                            {
                                if(val_getUnsignedInt(duracion, "\nDuracion: ", "\nError\n",3,20)== 0)
                                {
                                    if(val_getUnsignedInt(puntaje, "\nPuntaje: ", "\nError\n",3,20)== 0)
                                    {
                                        if(val_getAlfanumericoConSigno(linkImagen, "\nLink a imagen: ", "\nError\n",3,50)== 0)
                                        {
                                            do
                                            {
                                                val_getUnsignedInt(opcion, "\nGenero\n1-Comedia\n2-Terror\n3-Drama\n4-Ficcion\n5-Suspenso\n", "Opcion incorrecta\n", 3, 10);
                                                switch(atoi(opcion))
                                                {
                                                case 1:
                                                    arrayMovie[i].genero = GENERO_COMEDIA;
                                                    flagMotivo = 1;
                                                    break;
                                                case 2:
                                                    arrayMovie[i].genero = GENERO_TERROR;
                                                    flagMotivo = 1;
                                                    break;
                                                case 3:
                                                    arrayMovie[i].genero = GENERO_DRAMA;
                                                    flagMotivo = 1;
                                                    break;
                                                case 4:
                                                    arrayMovie[i].genero = GENERO_FICCION;
                                                    flagMotivo = 1;
                                                    break;
                                                case 5:
                                                    arrayMovie[i].genero = GENERO_SUSPENSO;
                                                    flagMotivo = 1;
                                                    break;
                                                }
                                                contadorIntentos ++;
                                            }
                                            while (flagMotivo == 1 && contadorIntentos < 3);
                                        }
                                    }
                                }
                                if(flagMotivo==1)
                                {
                                    strncpy(arrayMovie[indice].titulo, titulo, 20);
                                    strncpy(arrayMovie[indice].descripcion, descripcion, 50);
                                    arrayMovie[indice].duracion = atoi(duracion);
                                    arrayMovie[indice].puntaje = atoi(puntaje);
                                    strncpy(arrayMovie[indice].linkImagen, linkImagen, 50);
                                    movie_VolcarArchivoMovies(arrayMovie, longitud);
                                    retorno = 0;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            else
            {
                printf(msjError);
                break;
            }
        }
    }
    return retorno;
}


int informe_movie (EMovie* arrayMovie,int longitud)
{
    int i, retorno=-1;
    if(arrayMovie != NULL && longitud >= 0)
    {
        for(i=0; i<longitud; i++)
        {
            if(arrayMovie[i].estado == MOVIE_CARGADA)
            {
                printf("\nNombre de movie: %s\nGenero: %d\nDescripcion: %s\nDuracion: %d\nPuntaje: %d\nID: %d\n\n", arrayMovie[i].titulo,
                       arrayMovie[i].genero, arrayMovie[i].descripcion, arrayMovie[i].duracion, arrayMovie[i].puntaje, arrayMovie[i].id);
                retorno=0;
            }
        }
    }
    return retorno;
}


int movie_VolcarArchivoMovies(EMovie *arrayMovie, int longitud)
{
    FILE* pMovie;
    int cantidadEscrita;

    pMovie=fopen("archivoPelis.dat", "w");
    if(pMovie == NULL)
    {
        printf("IMPOSIBLE ABRIR EL ARCHIVO\n");
    }
    else
    {
        cantidadEscrita=fwrite(arrayMovie, sizeof(EMovie), longitud, pMovie);
    }
    if(cantidadEscrita < 1)
    {
        printf("error de carga\n");
    }
    fclose(pMovie);

    return 0;
}


int movie_LevantarArchivoMovies(EMovie *arrayMovie, int longitud)
{
    FILE* pMovie;
    int cantidadEscrita;

    pMovie=fopen("archivoPelis.dat", "r");
    if(pMovie == NULL)
    {
        printf("IMPOSIBLE ABRIR EL ARCHIVO\n");
    }
    else
    {
        cantidadEscrita=fread(arrayMovie, sizeof(EMovie), longitud, pMovie);
    }
    if(cantidadEscrita < 1)
    {
        printf("error de carga\n");
    }
    fclose(pMovie);

    return 0;
}


int movie_generarHTML(EMovie *arrayMovie, int longitud)
{
    FILE* pMovie;
    FILE* pEncabezadoDePagina;
    FILE* pCuerpoDePagina;
    char cuerpo[2000];
    char encabezado[2000];
    int i;

    pMovie=fopen("Archivo.html", "w");
    if(pMovie == NULL)
    {
        printf("IMPOSIBLE ABRIR EL ARCHIVO\n");
    }
    else
    {
        pEncabezadoDePagina=fopen("encabezado.txt", "r");
        fscanf(pEncabezadoDePagina,"%s", encabezado);
        fclose(pEncabezadoDePagina);
        fprintf(pMovie, "%s", encabezado);

        pCuerpoDePagina=fopen("cuerpo.txt", "r");
        fread(cuerpo, sizeof(char), 2000, pCuerpoDePagina);
        fclose(pCuerpoDePagina);

        for(i=0; i<longitud; i++)
        {
            if((arrayMovie + i)->estado == MOVIE_CARGADA)
            {
                fprintf(pMovie, cuerpo, (arrayMovie + i)->linkImagen,  (arrayMovie + i)->titulo,
                        (arrayMovie + i)->genero, (arrayMovie + i)->puntaje, (arrayMovie + i)->duracion, (arrayMovie + i)->descripcion);
            }
        }
    }
    fclose(pMovie);
    return 0;
}


