#ifndef JUGABILIDAD_H
#define JUGABILIDAD_H

bool combinaciones(unsigned  char * espacio, int filas , int columnas, int totalbytes, unsigned char* estado);
void rellenarespacios(unsigned  char * espacio, int filas , int columnas, int totalbytes, unsigned char* estado);
void mover_abajo(unsigned char *espacio, int filas, int columnas, int totalbytes);
#endif // JUGABILIDAD_H
