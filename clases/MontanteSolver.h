//
// Created by sergio on 22/08/21.
//

#ifndef PROGRAMA_METODO_MONTANTE_MONTANTESOLVER_H
#define PROGRAMA_METODO_MONTANTE_MONTANTESOLVER_H


// poder construir vectores
#include <vector>

class MontanteSolver {
public:
    // constructor MontanteSolver que recibe un vector de flotantes “matriz”
    explicit MontanteSolver(std::vector<std::vector<float>> &matriz);
    // método resolver
    std::vector<float> resolver();

private:
    // declaración de atributos
    std::vector<std::vector<float>> matriz;
    int numero_renglones_matriz;
    float pivote_anterior;
    float pivote_actual;

    // método cambiar renglón
    void cambiar_ren(int a, int b);
    // método para multiplicar en cruz
    void multiplicar_en_cruz(int indice_pivote, int indice_ren, int indice_columna);
};


#endif //PROGRAMA_METODO_MONTANTE_MONTANTESOLVER_H
