#ifndef JUGABILIDAD_H
#define JUGABILIDAD_H

bool combinaciones(unsigned  char * espacio, int filas , int columnas, int totalbytes, unsigned char* estado);
void rellenarespacios(unsigned  char * espacio, int filas , int columnas, int totalbytes, unsigned char* estado);
void mover_abajo(unsigned char *espacio, int filas, int columnas, int totalbytes);
int cascadas(unsigned char* espacio, int filas, int columnas,int totalbytes, int contador_cascadas, unsigned char* estado);
void eliminarfila(unsigned char* espacio, int* filas, int columnas,int totalbytes);
void eliminarcolumna(unsigned char* espacio, int filas, int* columnas,int totalbytes);
void eliminar_ficha(unsigned char* espacio,int filas, int columnas, int totalbytes, unsigned char*estado);
#endif // JUGABILIDAD_H
