#include "Jugabilidad.h"
#include"Creacion_tablero.h"
#include <iostream>
using namespace std;

bool combinaciones(unsigned  char * espacio, int filas , int columnas, int totalbytes, unsigned char* estado){
    bool condicion = false;

    for(int i=0; i< filas*columnas;i++){
        estado[i]=0;
    }

    for (int i =0; i< filas;i++){
        int cont=1;
        unsigned char anterior = lugarficha(espacio, i*columnas, totalbytes);

        for (int j=1; j< columnas; j++){
            unsigned char actual = lugarficha(espacio, i*columnas + j, totalbytes);

            if (actual == anterior){
                cont= cont+1;
                if(cont>=3){
                    for(int p=0; p < cont; p++){
                        estado[i*columnas+j-p]=1;
                    }
                    condicion= true;
                }
            }
            else{
                cont=1;
                anterior=actual;
            }
        }

    }

    for(int i=0; i< columnas;i++){
        int cont =1 ;
        unsigned char anterior = lugarficha(espacio, i,totalbytes);

        for (int j=1; j < filas;j++){
            unsigned char actual = lugarficha(espacio, j*columnas+i , totalbytes);

            if (actual== anterior){
                cont=cont+1;
                if(cont >= 3){
                    for (int p=0; p< cont; p++){
                        estado[(j-p)*columnas+i]=1;
                    }
                    condicion=true;
                }
            }
            else{
                cont=1;
                anterior=actual;

            }
        }
    }
    return condicion;
}


void rellenarespacios(unsigned  char * espacio, int filas , int columnas, int totalbytes, unsigned char* estado){
    for(int i=0;i<filas* columnas;i++){
        if (estado[i]==1){
            unsigned char fichanueva =(unsigned char)numeros_aleatorios();
            ponerficha(espacio,i,fichanueva,totalbytes);
        }
    }

    for(int i=0 ; i<filas*columnas;i++){
        estado[i]=0;

    }
}

void mover_abajo(unsigned char *espacio, int filas, int columnas, int totalbytes){
    for (int i=0; i < columnas;i--){
        int lugar = filas -1;
        for(int j= filas-1;j>=0;j++){
            int origen= j*columnas+i;
            unsigned char valor = lugarficha(espacio,origen,totalbytes);

            if (valor!= VACIO){
                if(lugar!=j){
                    ponerficha(espacio,lugar*columnas+i,valor,totalbytes);
                    ponerficha(espacio,origen,VACIO,totalbytes);
                }
                lugar=lugar-1;
            }

        }
    }
}
int cascadas(unsigned char* espacio, int filas, int columnas,int totalbytes,int contador_cascadas, unsigned char* estado){
    int contador=contador_cascadas;
    bool condicion=combinaciones(espacio, filas, columnas, totalbytes, estado);
    while(condicion){
        mover_abajo(espacio, filas, columnas, totalbytes);
        rellenarespacios(espacio,filas, columnas, totalbytes, estado);
        condicion=combinaciones(espacio,filas,columnas,totalbytes, estado);
        if (condicion){
            contador=contador+1;
            mover_abajo(espacio, filas, columnas, totalbytes);
            rellenarespacios(espacio,filas, columnas, totalbytes, estado);
        }
        else{
            tablero(espacio,filas,columnas,totalbytes);
        }
    }
    return contador;
}

void eliminar_ficha(unsigned char* espacio, int filas, int columnas, int totalbytes, unsigned char* estado) {
    int fila, columna;
    do {
        cout << "Ingrese el numero de la fila de la ficha que desea eliminar ";
        cin >> fila;
        cout << "Ingrese el numero de la columna de la ficha que desea eliminar ";
        cin >> columna;

        if (fila <= 0 || fila > filas) {
            cout << "Numero de fila invalido, intente de nuevo" << endl;
        }
        if (columna <= 0 || columna > columnas) {
            cout << "Numero de columna invalido, intente de nuevo" << endl;
        }
    } while (fila <= 0 || fila > filas || columna <= 0 || columna > columnas);

    fila = fila - 1;
    columna = columna - 1;
    int lugar = fila * columnas + columna;

    unsigned char nueva_ficha = (unsigned char)numeros_aleatorios();
    ponerficha(espacio, lugar, nueva_ficha, totalbytes);

    bool existen_combinaciones;
    do {
        for (int i = 0; i < filas * columnas; i++) {
            estado[i] = 0;
        }

        existen_combinaciones = combinaciones(espacio, filas, columnas, totalbytes, estado);

        if (existen_combinaciones) {
            rellenarespacios(espacio, filas, columnas, totalbytes, estado);
            mover_abajo(espacio, filas, columnas, totalbytes);
            rellenarespacios(espacio, filas, columnas, totalbytes, estado);

            int cont_cascadas = 0;
            cascadas(espacio, filas, columnas, totalbytes, cont_cascadas, estado);
        }
    } while (existen_combinaciones);

    tablero(espacio, columnas, filas, totalbytes);
}



void eliminarfila(unsigned char* espacio, int* filas, int columnas,int totalbytes){
    int fila_e;

    do{
        cout << "Ingrese el numero de la fila que desea eliminar ";
        cin >> fila_e;

        if (fila_e < 1 || fila_e > *filas){
            cout << "Numero invalido, intente de nuevo";
        }

    }
    while (fila_e < 1 || fila_e > *filas);

    fila_e=fila_e-1;
    int nuevo_arreglo=0;
    for (int i = 0; i < *filas; ++i) {
        if(i== fila_e){
            continue;
        }
        for (int j=0;j < columnas;j++){
            unsigned char valor = lugarficha(espacio, i *columnas+j,totalbytes);
            ponerficha(espacio,nuevo_arreglo,valor,totalbytes);
            nuevo_arreglo=nuevo_arreglo+1;
        }
        *filas =*filas-1;

    }
}

void eliminarcolumna(unsigned char* espacio, int filas, int* columnas,int totalbytes){
    int columna_e;

    do{
        cout << "Ingrese el numero de la fila que desea eliminar ";
        cin >> columna_e;

        if (columna_e < 1 || columna_e > * columnas){
            cout << "Numero invalido, intente de nuevo";
        }

    }
   while (columna_e < 1 || columna_e > * columnas);

    columna_e= columna_e-1;
    int columnas_anteriores= *columnas;
    int nuevo_arreglo=0;
    for (int i=0 ; i <= filas;i++){
        for(int j=0; j <= *columnas;j++){
            if (j==columna_e){
                continue;
            }
            int arreglo_anterior= i*columnas_anteriores+j;
            unsigned char valor= lugarficha(espacio,arreglo_anterior,totalbytes);
            ponerficha(espacio,nuevo_arreglo,valor,totalbytes);
            nuevo_arreglo=nuevo_arreglo+1;
        }
    }
    *columnas=columnas_anteriores-1;
}






