#include <iostream>

#include "clases/LectorMatriz.h"
#include "clases/MontanteSolver.h"

int main() {
    std::string ruta;
    char sn; // recibe respuesta sí o no.
    do {
        std::cout << "Introduzca la ruta del archivo: ";
        std::cin >> ruta;
        LectorMatriz lectorMatriz(ruta);
        std::vector<std::vector<int>> matriz = lectorMatriz.leerMatriz();
        MontanteSolver solucionador = MontanteSolver(matriz);
        solucionador.resolver();

        /* for (int i = 0; i < 2; ++i) {
            std::cout << std::endl;
            for (int j = 0; j < 3; ++j) {
                std::cout << matriz.at(i).at(j) << " ";
            }
        } */

        std::cout << std::endl << "¿Desea probar otro archivo? [S/n] ";
        std::cin >> sn;
    }while(sn != 'n');

    return 0;
}
