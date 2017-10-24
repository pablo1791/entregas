#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "validar.h"
#define CANT_PELICULAS 100

int main()
{

    EMovie arrayPeliculas[CANT_PELICULAS];
    movie_initArray(arrayPeliculas, CANT_PELICULAS);
    movie_LevantarArchivoMovies(arrayPeliculas, CANT_PELICULAS);

    char seguir='s';
    char opcion[10];

    do
    {
        val_getUnsignedInt(opcion, "1- Agregar pelicula\n2- Borrar pelicula\n3- Modificar pelicula\n4- Generar pagina web\n5- Salir\n",
                           "Ingrese un numero\n", 3, 10);
        switch(atoi(opcion))
        {
        case 1:
            movie_cargarMovie(arrayPeliculas, CANT_PELICULAS);
            break;
        case 2:
            movie_darDeBaja(arrayPeliculas, CANT_PELICULAS, "NO SE CARGARON PELICULAS\n");
            break;
        case 3:
            movie_modificar(arrayPeliculas, CANT_PELICULAS, "NO SE CARGARON PELICULAS\n");
            break;
        case 4:
            movie_generarHTML(arrayPeliculas, CANT_PELICULAS);
            break;
        case 5:
            seguir = 'n';
            break;
        default:
            printf("Error, ingrese opcion valida\n\n");
            break;
        }
    }
    while(seguir=='s');

    return 0;
}
