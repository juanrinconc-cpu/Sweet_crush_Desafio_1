#include <Creacion_tablero.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int mostrar_bienvenida(){
    ifstream archivo ("Intro.txt");

    if (!archivo){
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }
    string linea;

    while(getline(archivo,linea)){
        cout << linea << endl;
    }
    archivo.close();
    return 0;

}

int bytes_a_usar(int columnas, int filas){
    int bits = 3 * columnas * filas;
    int memoria_necesaria = bits/8;
    return memoria_necesaria;
}



unsigned char* creacion_tablero(int columnas, int filas){
    int n= bytes_a_usar(columnas,filas);
    unsigned char* tablero=new unsigned char(n);
    for (int i=1; i <= n;i++){
        tablero[i]=0;
    }
    return tablero;

}