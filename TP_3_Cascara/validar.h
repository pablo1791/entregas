#ifndef VALIDAR_H_INCLUDED
#define VALIDAR_H_INCLUDED



#endif // VALIDAR_H_INCLUDED

void myFgets(char* buffer, int limite ,FILE* archivo);

int val_getDNI(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarDni(char* buffer);

int val_getString(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarString(char* buffer);

int val_getUnsignedInt(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarUnsignedInt(char* buffer);

int val_getUnsignedEdad(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarUnsignedEdad(char* buffer);

int val_getAlfanumericoConSigno(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarAlfanumerico(char* buffer);

int val_getEmail(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarEmail(char* buffer);

int val_getFloat(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarFloat(char* buffer);

int val_getCuit(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarCuit(char* buffer);
