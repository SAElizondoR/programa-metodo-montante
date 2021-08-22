//
// Created by sergioaer on 22/08/21.
//

#include <sstream>
#include <iterator>

#include "LectorMatriz.h"

void LectorMatriz::irInicioArchivo() {
    archivo.clear();
    archivo.seekg(0);
}

int LectorMatriz::contarRenglonesArchivo() {
    // recorre el archivo contando los saltos de línea (\n)
    int numeroRenglones = int(std::count(std::istreambuf_iterator<char>(archivo),
                                         std::istreambuf_iterator<char>(), '\n'));
    irInicioArchivo(); // regresa al inicio después de contar renglones
    return numeroRenglones;
}

LectorMatriz::LectorMatriz(const std::string &ruta) {
    archivo.open(ruta);    // abre el archivo
}

std::vector<std::vector<int>> LectorMatriz::leerMatriz() {
    int n = contarRenglonesArchivo();
    // matriz de n * (n + 1)
    std::vector<std::vector<int>> matriz;

    for (int i = 0; i < n; ++i) {
        std::string linea_archivo;
        std::getline(archivo, linea_archivo);

        std::istringstream flujo_linea_archivo(linea_archivo);  // crea un flujo a partir de la línea
        std::vector<int> ren_matriz((std::istream_iterator<int>(flujo_linea_archivo)),
                                    std::istream_iterator<int>());  // lee todos los números del renglón
        matriz.push_back(ren_matriz);   // mete el renglón al final de la matriz
    }

    return matriz;
}
