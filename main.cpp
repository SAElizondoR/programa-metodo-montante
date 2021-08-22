#include <iostream>

#include "clases/LectorMatriz.h"

int main() {
    std::string ruta;
    char sn; // recibe respuesta sí o no.
    do {
        std::cout << "Introduzca la ruta del archivo: ";
        std::cin >> ruta;
        LectorMatriz lectorMatriz(ruta);
        lectorMatriz.leerMatriz();

        std::cout << std::endl << "¿Desea probar otro archivo? [S/n] ";
        std::cin >> sn;
    }while(sn != 'n');

    return 0;
}
