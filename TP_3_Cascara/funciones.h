#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct{
    char titulo[20];
    int genero;
    int duracion;
    char descripcion[50];
    int puntaje;
    char linkImagen[50];
    unsigned int estado;
    unsigned int id;
}EMovie;

#endif // FUNCIONES_H_INCLUDED

#define MOVIE_NO_CARGADA -1
#define MOVIE_CARGADA 0

#define GENERO_COMEDIA 1
#define GENERO_TERROR 2
#define GENERO_DRAMA 3
#define GENERO_FICCION 4
#define GENERO_SUSPENSO 5

int movie_initArray (EMovie* arrayMovie, int longitud);
int movie_generarProximoId (void);
int movie_cargarMovie (EMovie* arrayMovie,int longitud);
int movie_buscarIndicePorId (EMovie* arrayMovie, int longitud, int id, char* mensaje);
int movie_darDeBaja (EMovie* arrayMovie,int longitud, char* msjError);
int movie_modificar (EMovie* arrayMovie,int longitud, char* msjError);

int informe_movie (EMovie* arrayMovie,int longitud);
int movie_generarHTML(EMovie *arrayMovie, int longitud);

int movie_VolcarArchivoMovies(EMovie *arrayMovie, int longitud);
int movie_LevantarArchivoMovies(EMovie *arrayMovie, int longitud);

