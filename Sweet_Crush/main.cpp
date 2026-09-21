#include <iostream>
#include "Creacion_tablero.h"
#include "jugabilidad.h"
using namespace std;

int main()
{
    srand((unsigned int)time(NULL));
    cout << "---Bienvenido a Sweet Crush--- " << endl;
    mostrar_bienvenida();
    bool condicion_juego = true;

    while (condicion_juego) {
        int opcion;
        cout << "---Menu principal--- " << endl;
        cout << "1. para jugar " << endl;
        cout << "2. para salir " << endl;
        cin >> opcion;
        cout << endl;

        switch (opcion) {
        case 1:
            cout << "Iniciando partida... " << endl;
            {
                int cont_movimientos = 0;
                int eliminar_filas = 0;
                int cont_eliminar_columnas = 0;
                int filas;
                int columnas;
                int bytesreservados;
                unsigned char* espacio = nullptr;

                informaciontablero(&filas, &columnas, &bytesreservados, &espacio);


                int total_celdas = filas * columnas;
                unsigned char* estado = new unsigned char[total_celdas];
                for (int i = 0; i < total_celdas; i++) {
                    estado[i] = 0;
                }

                tablero(espacio, columnas, filas, bytesreservados);
                ubicacion_fichas(filas, columnas);

                int opcion_partida;
                do {
                    cout << "--Menu partida--" << endl;
                    cout << "1. eliminar ficha " << endl;
                    cout << "2. eliminar fila " << endl;
                    cout << "3. eliminar columna" << endl;
                    cout << "0. para salir de la partida" << endl;

                    cout << "Selecciona una opcion: ";
                    cin >> opcion_partida;

                    if (opcion_partida < 0 || opcion_partida > 3) {
                        cout << "opcion invalida, seleccione de nuevo" << endl;
                        continue;
                    }

                    switch (opcion_partida) {
                    case 1:
                        eliminar_ficha(espacio, filas, columnas, bytesreservados, estado);
                        cont_movimientos=cont_movimientos+1;
                        tablero(espacio,columnas,filas,bytesreservados);
                        break;
                    case 2:
                        eliminarfila(espacio, &filas, columnas, bytesreservados);
                        eliminar_filas=eliminar_filas+1;
                        tablero(espacio,columnas,filas,bytesreservados);
                        break;
                    case 3:
                        eliminarcolumna(espacio, filas, &columnas, bytesreservados);
                        cont_eliminar_columnas=cont_eliminar_columnas+1;
                        tablero(espacio,columnas,filas,bytesreservados);
                        break;
                    }

                    cout << "llevas " << cont_movimientos << " movimientos realizados" << endl;
                    cout << "llevas " << eliminar_filas << " filas eliminadas" << endl;
                    cout << "llevas " << cont_eliminar_columnas << " columnas eliminadas" << endl;

                } while (opcion_partida != 0);

                delete[] espacio;
                delete[] estado;
            }
            break;

        case 2:
            cout << "saliendo..." << endl;
            condicion_juego = false;
            break;
        }
    }

    return 0;
}

