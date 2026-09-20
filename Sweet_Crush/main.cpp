#include <iostream>
#include "Creacion_tablero.h"
#include "jugabilidad.h"
using namespace std;

int main()
{
    srand((unsigned int)time(NULL));
    cout << "---Bienvenido a Sweet Crush--- " << endl;
    mostrar_bienvenida();

    int filas;
    int columnas;
    int bytesreservados;
    unsigned char* espacio;

    informaciontablero(&filas,&columnas,&bytesreservados,&espacio);
    tablero(espacio,columnas,filas,bytesreservados);
    ubicacion_fichas(filas,columnas);

    delete[]espacio;

    return 0;

}
