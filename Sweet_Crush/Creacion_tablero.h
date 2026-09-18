#ifndef CREACION_TABLERO_H
#define CREACION_TABLERO_H

const int fmaxima=45;
const int cmaxima=20;
const unsigned char X =0;
const unsigned char O =1;
const unsigned char W =2;
const unsigned char K =3;
const unsigned char B =4;
const unsigned char C =5;
char crear_ficha(unsigned char valor);
void mostrar_bienvenida();
int bytes_a_usar(int columnas,int filas);
unsigned char lugarficha(const unsigned char* espacio ,int indice, int totalBytes);
unsigned char* creacion_tablero(int columnas, int filas);
void ponerficha(unsigned char* espacio,int indice, unsigned char valor, int totalBytes);
int numeros_aleatorios();
unsigned int aleatorio();
unsigned char* creacion_tablero(int columnas, int filas, int totalbytes);
void tablero(const unsigned char* espacio, int columnas,int filas, int totalbytes);
void informaciontablero(int* filas, int*columnas, int* bytesreservados, unsigned char ** espacio);

#endif // CREACION_TABLERO_H
