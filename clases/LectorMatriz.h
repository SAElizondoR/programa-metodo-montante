//
// Created by sergioaer on 22/08/21.
//

#ifndef PROGRAMA_METODO_MONTANTE_LECTORMATRIZ_H
#define PROGRAMA_METODO_MONTANTE_LECTORMATRIZ_H


#include <string>
#include <fstream>
#include <vector>

class LectorMatriz {
public:
    explicit LectorMatriz(std::string const& ruta);
    std::vector<std::vector<int>> leerMatriz();

private:
    std::ifstream archivo;

    void irInicioArchivo();
    int contarRenglonesArchivo();
};


#endif //PROGRAMA_METODO_MONTANTE_LECTORMATRIZ_H
