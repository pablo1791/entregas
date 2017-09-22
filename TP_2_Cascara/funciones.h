#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct {

    char nombre[50];
    unsigned char edad;
    int estado;
    char dni[15];

}EPersona;

#endif // FUNCIONES_H_INCLUDED

#define LUGAR_LIBRE 0
#define LUGAR_OCUPADO 1

int persona_initArray (EPersona* arrayPersona, int longitud);
int persona_buscaProxId (EPersona* arrayPersona, int longitud);
int persona_cargarPersona (EPersona* arrayPersona, int longitud);

int persona_buscarPorDni(EPersona* arrayPersona, char* dni, int longitud,char mensajeError[]);

int persona_bajaPersona (EPersona* arrayPersona,int longitud);

int persona_ordenar(EPersona* arrayPersona, int longitud);

int persona_printPersona (EPersona* arrayPersona, int longitud);

void persona_imprimirGraficoEdades(EPersona arrayPersona[],int longitud);







