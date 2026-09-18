#include "Jugabilidad.h"
#include"Creacion_tablero.h"

bool combinaciones(const unsigned  char * espacio, int filas , int columnas, int totalbytes, unsigned char* estado){
    bool condicion = false;

    for (int i =0; i< filas;i++){
        int cont=1;
        unsigned char anterior = lugarficha(espacio, i*columnas, totalbytes);

        for (int j=1; j< columnas; j++){
            unsigned char actual = lugarficha(espacio, i*columnas + j, totalbytes);

            if (actual == anterior){
                cont= cont+1;
                if(cont==3){
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
                if(cont == 3){
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
