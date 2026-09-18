#include "Creacion_tablero.h"
#include <iostream>
#include <string>
#include <fstream>



using namespace std;

/*
La función "mostrar bienvenida" , toma el archivo llamado Intro.txt
Lo imprime linea por linea, si el archivo no es leido lanza un
aviso en pantalla y continua sin romper la estructura, emulando
un stop controlado.
*/

void mostrar_bienvenida(){
    ifstream archivo("Intro.txt");

    if (!archivo){
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
    string linea;

    while(getline(archivo,linea)){
        cout << linea << endl;
    }
    archivo.close();

}

int bytes_a_usar(int columnas, int filas){
    int bits = 3 * columnas * filas;
    int memoria_necesaria = (bits+7)/8;
    return memoria_necesaria;

}
/*
La función "ficha", requiere de 3 parametros un puntero hacia espacio
que es el punto exacto donde tenemos todas las fichas "empaquetadas" las fichas en este caso
se manejan en bytes que continen 8 bits y cada ficha representa 3 bits,
el controlador del espacio de memoria sera totalBytes.
si el indice es 5 la ficha empieza en el bit 15
el byte en el que se encuetra sera el segundo byte y la ficha empieza en el bit 7 de ese byte
Notese tambien el uso de una mascara para extraer los 3 bits
*/

unsigned char lugarficha(const unsigned char* espacio ,int indice, int totalBytes){
    int bit_inicial = indice* 3;
    int byte_inicial =bit_inicial/8;
    int desplazamiento = bit_inicial%8;

    unsigned short punto = espacio[byte_inicial];
    if (byte_inicial+1 < totalBytes){
        punto = punto | (unsigned short) espacio[byte_inicial +1] << 8;

    }
    return (unsigned char) ((punto >> desplazamiento) & 0x07);
}

char crear_ficha(unsigned char opcion){
    static const char tabla[]={X,O,W,K,B,C};
    const char *ptr = tabla;

    if (opcion==X){
        return *(ptr+0);

    }
    else if(opcion==O){
        return *(ptr+1);
    }
    else if(opcion==W){
        return *(ptr+2);
    }
    else if(opcion==K){
        return *(ptr+3);
    }
    else if(opcion==B){
        return *(ptr+4);
    }
    else if(opcion==C){
        return *(ptr+5);
    }
    else {
        return *(ptr+6);
    }
}

void ponerficha(unsigned char* espacio,int indice, unsigned char valor, int totalBytes){
    int bit_inicial = indice* 3;
    int byte_inicial =bit_inicial/8;
    int desplazamiento = bit_inicial%8;

    bool byte_siguiente = (byte_inicial + 1) < totalBytes;

    unsigned short punto = espacio[byte_inicial];
    if (byte_siguiente){
        punto = punto | (unsigned short) espacio[byte_inicial +1] << 8;

    }

    unsigned short mascara= ~((unsigned short)0x07 << desplazamiento);
    punto= punto & mascara;
    punto = punto | ((unsigned short)(valor & 0x07) << desplazamiento);

    espacio[byte_inicial]=(unsigned char)(punto & 0xFF);
    if (byte_siguiente){
        espacio[byte_inicial+1] = (unsigned char)((punto >> 8) & 0xFF);
    }


}

unsigned int aleatorio(){
    static unsigned int estado=(unsigned int)time(nullptr)|1;
    estado = estado ^ estado << 13;
    estado = estado ^ estado>> 17;
    estado = estado ^ estado << 5;
    return estado;
}


int numeros_aletorios(){
    int numero = aleatorio();
        return (numero % 6);


}


unsigned char* creacion_tablero(int columnas, int filas, int totalbytes){
    unsigned char* espacio= new unsigned char [totalbytes];
    for (int i= 0; i< totalbytes; i++){
        espacio[i]=0;
    }
    int posiciones= filas * columnas;
    for (int i=0; i< posiciones;i++){
        unsigned char valor = (unsigned char)numeros_aletorios();
        ponerficha(espacio, i, valor, totalbytes);
    }
    return espacio;

}
void tablero(const unsigned char* espacio, int columnas,int filas, int totalbytes){
    for (int i=0; i< filas;i++){
        for (int j=0; j< columnas;j++){
            int indice= i*columnas+j;
            unsigned char valor = lugarficha(espacio, indice, totalbytes);
            char representacion= crear_ficha(valor);
            cout <<representacion << " ";
        }

        cout << endl << endl;
    }
}


void informaciontablero(int* filas, int*columnas, int* bytesreservados, unsigned char ** espacio){
    int f;
    int c;

    do{
        cout << "ingrese el numero de filas [1 a " << fmaxima << " ]:";
        cin>> f;

        if (f<=0 || f > fmaxima){
            cout << "Numero de filas invalido, intente nuveamente" << endl;

        }
    }
        while (f <=0 ||f > fmaxima);

    do{
        cout << "ingrese el numero de columnas [1 a " << cmaxima << " ]:";
        cin>> c;

        if (c<=0 || c > cmaxima){
            cout << "Numero de columnas invalido, intente nuveamente" << endl;

        }
    }
    while (c<=0 ||c > cmaxima);

    *filas=f;
    *columnas=c;
    *bytesreservados=bytes_a_usar(c,f);
    *espacio = creacion_tablero(c,f,*bytesreservados);





}


