//
// Created by sergio on 22/08/21.
//

#ifndef PROGRAMA_METODO_MONTANTE_MONTANTESOLVER_H
#define PROGRAMA_METODO_MONTANTE_MONTANTESOLVER_H


#include <vector>

class MontanteSolver {
public:
    explicit MontanteSolver(std::vector<std::vector<int>>& matriz);
    std::vector<int> resolver();

private:
    std::vector<std::vector<int>> matriz;
    int numero_renglones_matriz;
    int pivote_anterior;
    int pivote_actual;

    void cambiar_ren(int a, int b);
    void multiplicar_en_cruz(int indice_pivote, int indice_ren, int indice_columna);
};


#endif //PROGRAMA_METODO_MONTANTE_MONTANTESOLVER_H
