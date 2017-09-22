#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "validaciones.h"
#define CANT 200


int main()
{
    EPersona persona[CANT];
    persona_initArray(persona, CANT);


    char buffer[10];

    do
    {
        val_getUnsignedInt(buffer,"1- Agregar persona\n2- Borrar persona\n3- Imprimir lista ordenada por nombre\n4- Imprimir grafico de edades\n\n5- Salir\n","Opcion invalida\n", 3, 10);

        switch(atoi(buffer))
        {
        case 1:
            persona_cargarPersona(persona, CANT);
            break;
        case 2:
            persona_bajaPersona(persona, CANT);
            break;
        case 3:
            persona_printPersona(persona, CANT);
            break;
        case 4:
            persona_imprimirGraficoEdades(persona, CANT);
            break;
        case 5:

            break;
        }
    }
    while(atoi(buffer) != 5);


    return 0;
}
