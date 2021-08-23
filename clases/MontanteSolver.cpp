//
// Created by sergio on 22/08/21.
//

#include <iostream>
#include "MontanteSolver.h"


MontanteSolver::MontanteSolver(std::vector<std::vector<int>> &matriz) {
    this->matriz = matriz;
    numero_renglones_matriz = int(matriz.size());
    pivote_anterior = 1;
    pivote_actual = 1;
}

void MontanteSolver::resolver() {
    bool pivote_es_cero = false;
    for (int indice_pivote = 0; indice_pivote < numero_renglones_matriz; ++indice_pivote) {
        pivote_anterior = pivote_actual;
        pivote_actual = matriz.at(indice_pivote).at(indice_pivote);
        if (pivote_actual == 0) {
            pivote_es_cero = true;
            for (int indice_intercambio = indice_pivote + 1; indice_intercambio < numero_renglones_matriz;
            ++indice_intercambio) {
                if (matriz.at(indice_intercambio).at(indice_pivote) != 0) {
                    cambiar_ren(indice_pivote, indice_intercambio);
                    pivote_es_cero = false;
                    break;
                }
            }
        }
        if (!pivote_es_cero) {
            for (int indice_ren = 0; indice_ren < indice_pivote; ++indice_ren) {
                for (int indice_col = indice_pivote + 1; indice_col < numero_renglones_matriz + 1; ++indice_col) {
                    multiplicar_en_cruz(indice_pivote, indice_ren, indice_col);
                }
            }
            for (int indice_ren = indice_pivote + 1; indice_ren < numero_renglones_matriz; ++indice_ren) {
                for (int indice_col = indice_pivote + 1; indice_col < numero_renglones_matriz + 1; ++indice_col) {
                    multiplicar_en_cruz(indice_pivote, indice_ren, indice_col);
                }
            }
            for (int indice = 0; indice < indice_pivote; ++indice) {
                matriz.at(indice).at(indice) = pivote_actual;
            }
            for (int indice_ren = 0; indice_ren < indice_pivote; ++indice_ren) {
                matriz.at(indice_ren).at(indice_pivote) = 0;
            }
            for (int indice_ren = indice_pivote + 1; indice_ren < numero_renglones_matriz; ++indice_ren) {
                matriz.at(indice_ren).at(indice_pivote) = 0;
            }
        }
    }
    for (int i = 0; i < numero_renglones_matriz; ++i) {
        std::cout << matriz[i][numero_renglones_matriz] / matriz[i][i] << std::endl;
    }
}

void MontanteSolver::cambiar_ren(int a, int b) {
    int temp;
    for (int i = 0; i < numero_renglones_matriz + 1; ++i) {
        temp = matriz.at(a).at(i);
        matriz.at(a).at(i) = matriz.at(b).at(i);
        matriz.at(b).at(i) = temp;
    }
    pivote_actual = matriz.at(b).at(b);
}

void MontanteSolver::multiplicar_en_cruz(int indice_pivote, int indice_ren, int indice_col) {
    matriz.at(indice_ren).at(indice_col) = (matriz.at(indice_ren).at(indice_col) *
            matriz.at(indice_pivote).at(indice_pivote) - matriz.at(indice_ren).at(indice_pivote) *
            matriz.at(indice_pivote).at(indice_col)) / pivote_anterior;
}
